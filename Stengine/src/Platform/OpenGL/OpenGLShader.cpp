#include "stpch.h"
#include "OpenGLShader.h"

#include "Stengine/Core/Timer.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

namespace Sten
{
	namespace Utils {

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:   return shaderc_glsl_vertex_shader;
				case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
			}

			ST_CORE_ASSERT(false);
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
				case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}

			ST_CORE_ASSERT(false);
			return nullptr;
		}

		static const char* GetCacheDirectory()
		{
			// TODO: make sure the assets directory is valid
			return "assets/cache/shader/opengl";
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
		{
			switch (stage)
			{
				case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
				case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
			}
			ST_CORE_ASSERT(false);
			return "";
		}
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string content;
		std::ifstream io(filePath, std::ios::in | std::ios::binary);
		if (!io)
		{
			ST_CORE_ERROR("Couldn't find file: '{0}'", filePath);
			return "";
		}

		io.seekg(0, std::ios::end);
		content.resize(io.tellg());
		io.seekg(0, std::ios::beg);
		io.read(&content[0], content.size());
		io.close();
		return content;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex, const std::string& fragment, bool isSource)
		: m_Name(name)
	{
		Utils::CreateCacheDirectoryIfNeeded();

		std::string vertexSrc = isSource ? vertex : ReadFile(vertex);
		std::string fragmentSrc = isSource ? fragment : ReadFile(fragment);
		if (!isSource)
		{
			m_VertexPath = vertex;
			m_FragmentPath = fragment;
		}

		{
			Timer timer;
			CompileOrGetVulkanBinaries(vertexSrc, fragmentSrc);
			CompileOrGetOpenGLBinaries();
			CreateProgram();
			ST_CORE_WARN("Shader creation took {0} ms", timer.ElapsedMillis());
		}

		CompileOrGetVulkanBinaries(vertexSrc, fragmentSrc);
		CompileOrGetOpenGLBinaries();
		CreateProgram();
	}

	void OpenGLShader::CompileOrGetVulkanBinaries(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLuint program = glCreateProgram();

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		auto& shaderData = m_VulkanSPIRV;
		shaderData.clear();
		CompileShader(compiler, options, m_VertexPath, vertexSrc, true);
		CompileShader(compiler, options, m_FragmentPath, fragmentSrc, false);

		for (auto&& [stage, data] : shaderData)
			Reflect(stage, data);
	}

	void OpenGLShader::CompileShader(shaderc::Compiler& compiler, shaderc::CompileOptions& options, const std::string& filePath, const std::string& source, bool isVertex)
	{
		std::string extension = isVertex ? ".cached_vulkan.vert" : ".cached_vulkan.frag";

		std::filesystem::path cachedPath = 
			((std::filesystem::path)Utils::GetCacheDirectory()) / 
			(((std::filesystem::path)filePath).filename().string() + extension);

		std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
		if (in.is_open())
		{
			in.seekg(0, std::ios::end);
			auto size = in.tellg();
			in.seekg(0, std::ios::beg);

			auto& data = m_VulkanSPIRV[isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER];
			data.resize(size / sizeof(uint32_t));
			in.read((char*)data.data(), size);
		}
		else
		{
			shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, isVertex ? shaderc_glsl_vertex_shader : shaderc_glsl_fragment_shader, filePath.c_str(), options);
			if (module.GetCompilationStatus() != shaderc_compilation_status_success)
			{
				ST_CORE_ERROR(module.GetErrorMessage());
				ST_CORE_ASSERT(false);
			}

			m_VulkanSPIRV[isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER] = std::vector<uint32_t>(module.cbegin(), module.cend());

			std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
			if (out.is_open())
			{
				auto& data = m_VulkanSPIRV[isVertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER];
				out.write((char*)data.data(), data.size() * sizeof(uint32_t));
				out.flush();
				out.close();
			}
		}
	}

	void OpenGLShader::CompileOrGetOpenGLBinaries()
	{
		auto& shaderData = m_OpenGLSPIRV;

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = false;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		shaderData.clear();
		m_OpenGLSourceCode.clear();
		for (auto&& [stage, spirv] : m_VulkanSPIRV)
		{
			std::string filePath;
			std::string extension;
			switch (stage)
			{
			case GL_VERTEX_SHADER:
				filePath = m_VertexPath;
				extension = ".cached_opengl.vert";
				break;
			case GL_FRAGMENT_SHADER:
				filePath = m_FragmentPath;
				extension = ".cached_opengl.frag";
				break;
			default:
				ST_CORE_ASSERT(false, "Unknown shader stage");
				return;
			}

			std::filesystem::path cachedPath = cacheDirectory / (((std::filesystem::path)filePath).filename().string() + extension);

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv);
				m_OpenGLSourceCode[stage] = glslCompiler.compile();
				auto& source = m_OpenGLSourceCode[stage];

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), filePath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					ST_CORE_ERROR(module.GetErrorMessage());
					ST_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
	}

	void OpenGLShader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_OpenGLSPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			ST_CORE_ERROR("Shader linking failed ({0}, {1}):\n{1}", m_VertexPath, m_FragmentPath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}

		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		ST_CORE_TRACE("OpenGLShader::Reflect - {0} {1} {2}", Utils::GLShaderStageToString(stage), m_VertexPath, m_FragmentPath);
		ST_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		ST_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		ST_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = bufferType.member_types.size();

			ST_CORE_TRACE("  {0}", resource.name);
			ST_CORE_TRACE("    Size = {0}", bufferSize);
			ST_CORE_TRACE("    Binding = {0}", binding);
			ST_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform1i(location, value);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform1iv(location, count, values);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform1f(location, value);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform2f(location, value.x, value.y);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform3f(location, value.x, value.y, value.z);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniform4f(location, value.x, value.y, value.z, value.w);
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location >= 0)	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		else				ST_CORE_ERROR("Couldn't find uniform '{0}'.", name);
	}

}

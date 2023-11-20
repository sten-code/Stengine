#include "stpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sten
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		ST_CORE_ASSERT(windowHandle, "Window Handle is null.");
	}

	void OpenGLContext::Init()
	{
		ST_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ST_CORE_ASSERT(status, "Failed to initialize Glad.");

		ST_CORE_INFO("OpenGL Info:");
		ST_CORE_INFO("    Vendor:   {0}", (char*)glGetString(GL_VENDOR));
		ST_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));
		ST_CORE_INFO("    Version:  {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		ST_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
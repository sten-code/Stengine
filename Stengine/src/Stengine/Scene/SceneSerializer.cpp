#include "stpch.h"
#include "SceneSerializer.h"

#include "Stengine/Scene/Entity.h"
#include "Stengine/Scene/Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Sten
{
	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		: m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "234562345"; // TODO: Entity ID
		out << YAML::EndMap;

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;

				SerializeEntity(out, entity);
			});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filePath)
	{
		ST_CORE_ASSERT(false, "Unimplemented");
	}

	void SceneSerializer::Deserialize(const std::string& filePath)
	{

	}

	void SceneSerializer::DeserializeRuntime(const std::string& filePath)
	{
		ST_CORE_ASSERT(false, "Unimplemented");
	}
}
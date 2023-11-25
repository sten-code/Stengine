#pragma once

#include "Stengine/Core/Core.h"
#include "Stengine/Scene/Scene.h"

#include <yaml-cpp/yaml.h>

namespace Sten
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filePath);
		void SerializeRuntime(const std::string& filePath);

		bool Deserialize(const std::string& filePath);
		void DeserializeRuntime(const std::string& filePath);
	private:
		void SerializeEntity(YAML::Emitter& out, Entity entity);
	private:
		Ref<Scene> m_Scene;
	};

}
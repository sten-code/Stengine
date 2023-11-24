#pragma once

#include "Stengine/Core/Core.h"
#include "Stengine/Scene/Scene.h"

namespace Sten
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filePath);
		void SerializeRuntime(const std::string& filePath);

		void Deserialize(const std::string& filePath);
		void DeserializeRuntime(const std::string& filePath);
	private:
		Ref<Scene> m_Scene;
	};
}
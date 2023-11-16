#pragma once

#include <Stengine.h>

class Sandbox2D : public Sten::Layer
{
public:
	Sandbox2D();

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Sten::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Sten::Event& e) override;
private:
	Sten::ShaderLibrary m_ShaderLibrary;
	Sten::OrthographicCameraController m_CameraController;

	glm::vec4 m_Color = { 0.8f, 0.2f, 0.3f, 1.0f };
	Sten::Ref<Sten::Texture2D> m_Texture;
	Sten::Ref<Sten::VertexArray> m_VertexArray;

	float m_Fps = 0.0f;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};
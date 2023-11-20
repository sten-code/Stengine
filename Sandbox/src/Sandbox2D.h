#pragma once

#include <Stengine.h>
#include "ParticleSystem.h"

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
	ParticleSystem m_ParticleSystem;

	glm::vec4 m_Color = { 0.8f, 0.2f, 0.3f, 1.0f };
	Sten::Ref<Sten::Texture2D> m_Texture;
	Sten::Ref<Sten::VertexArray> m_VertexArray;
	Sten::Ref<Sten::Texture2D> m_Tilemap;
	Sten::Ref<Sten::SubTexture2D> m_SubTexture;
	Sten::Ref<Sten::Framebuffer> m_Framebuffer;

	ParticleProps m_Particle;

	float m_Fps = 0.0f;
};
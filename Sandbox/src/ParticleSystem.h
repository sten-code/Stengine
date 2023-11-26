#pragma once

#include <Stengine.h>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec2 Acceleration, AccelerationVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
	bool Normalized = false;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t maxParticles = 100000);

	void OnUpdate(Sten::Timestep ts);
	void OnRender(const glm::mat4& viewProjection);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec2 Acceleration;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;
		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
		bool Normalized = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 0;
};
#pragma once

#include <glm/glm.hpp>

namespace Sten
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_Projection(projection) {}
		virtual ~Camera() = default;

		const glm::mat4 GetProjection() const { return m_Projection; }
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 position) { m_Position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

		inline const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4 GetViewProjectionMatrix() const { return m_ViewProjecionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjecionMatrix;

		OrthographicCameraBounds m_Bounds;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}
#include "stpch.h"
#include "Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Sten
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale)
	{
		using T = float;

		glm::mat4 localMatrix(transform);

		if (glm::epsilonEqual(localMatrix[3][3], static_cast<T>(0), glm::epsilon<T>()))
			return false;

		if (glm::epsilonNotEqual(localMatrix[0][3], static_cast<T>(0), glm::epsilon<T>()) ||
			glm::epsilonNotEqual(localMatrix[1][3], static_cast<T>(0), glm::epsilon<T>()) ||
			glm::epsilonNotEqual(localMatrix[2][3], static_cast<T>(0), glm::epsilon<T>()))
		{
			localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = static_cast<T>(0);
			localMatrix[3][3] = static_cast<T>(1);
		}

		outTranslation = localMatrix[3];
		localMatrix[3] = { 0, 0, 0, localMatrix[3].w };

		glm::vec3 row[3];

		for (glm::length_t i = 0; i < 3; ++i)
			for (glm::length_t j = 0; j < 3; ++j)
				row[i][j] = localMatrix[i][j];

		outScale.x = glm::length(row[0]);
		row[0] = glm::detail::scale(row[0], static_cast<T>(1));
		outScale.y = glm::length(row[1]);
		row[1] = glm::detail::scale(row[1], static_cast<T>(1));
		outScale.z = glm::length(row[2]);
		row[2] = glm::detail::scale(row[2], static_cast<T>(1));

		outRotation.y = asin(-row[0][2]);
		if (cos(outRotation.y) != 0)
		{
			outRotation.x = atan2(row[1][2], row[2][2]);
			outRotation.z = atan2(row[0][1], row[0][0]);
		}
		else
		{
			outRotation.x = atan2(-row[2][0], row[1][1]);
			outRotation.z = 0;
		}

		return true;
	}
}
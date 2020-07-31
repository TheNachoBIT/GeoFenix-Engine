#include "Object.h"

namespace geofenix
{
	namespace graphics
	{
		Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
		{
			position = pos;
			scale = sca;
			rotation = rot;
		}

		glm::mat3 rodriguesMatrix(const double degrees, const glm::vec3& axis) {
			glm::mat3 v = glm::mat3(
				axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
				axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
				axis.x * axis.z, axis.y * axis.z, axis.z * axis.z
			);

			glm::mat3 v2 = glm::mat3(
				0, -axis.z, axis.y,
				axis.z, 0, -axis.x,
				-axis.y, axis.x, 0
			);
			glm::mat3 cosMat(1.0f * cos(degrees * M_PI));
			v *= (1 - cos(degrees * M_PI));
			v2 *= sin(degrees * M_PI);

			glm::mat3 rotation = cosMat + v + v2;

			return rotation;
		}

		Vertex* Object::UpdateObject(Vertex* target)
		{
			glm::mat3 rotationMatrix;
			rotationMatrix = rodriguesMatrix(glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			rotationMatrix = rodriguesMatrix(glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			rotationMatrix = rodriguesMatrix(glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));


			float size = 1.0f;
			target->position = rotationMatrix * glm::vec3(position.x - 0.5f * scale.x, position.y + 0.5f * scale.y, position.z);
			target->color = glm::vec3(1.0f, 0.2f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 1.0f);
			target++;

			target->position = rotationMatrix * glm::vec3(position.x - 0.5f * scale.x, position.y - 0.5f * scale.y, position.z);
			target->color = glm::vec3(0.2f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 0.0f);
			target++;

			target->position = rotationMatrix * glm::vec3(position.x + 0.5f * scale.x, position.y - 0.5f * scale.y, position.z);
			target->color = glm::vec3(0.2f, 0.2f, 1.0f);
			target->texcoord = glm::vec2(1.0f, 0.0f);
			target++;

			target->position = rotationMatrix * glm::vec3(position.x + 0.5f * scale.x, position.y + 0.5f * scale.y, position.z);
			target->color = glm::vec3(1.0f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(1.0f, 1.0f);
			target++;

			return target;
		}
	}
}

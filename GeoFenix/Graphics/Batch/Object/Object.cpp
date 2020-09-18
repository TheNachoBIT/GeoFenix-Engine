#include "Object.h"

namespace geofenix
{
	namespace graphics
	{
		Object::Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, int ObjId)
			: translationMatrix(glm::mat4(0)), rotationMatrix(glm::mat4(0))
		{
			id = ObjId;
			position = pos;
			lastPosition = pos + glm::vec3(1.0f);
			scale = sca;
			rotation = rot;
			lastRotation = rot + glm::vec3(1.0f);
		}

		glm::mat4 One(1.0f);
		Vertex* Object::UpdateObject(Vertex* target)
		{
			if (lastPosition != position)
			{
				translationMatrix = glm::translate(One, -position);
				lastPosition = position;
			}

			if (lastRotation != rotation)
			{
				glm::quat rot;
				rot = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
				rot = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
				rot = glm::angleAxis(glm::radians(rotation.z + 180.f), glm::vec3(0.0f, 0.0f, 1.0f));

				rotationMatrix = -translationMatrix * glm::toMat4(rot) * translationMatrix;
				lastRotation = rotation;
			}

			target->position = glm::vec4(position.x - 0.5f * scale.x, position.y + 0.5f * scale.y, position.z, 1.0f);
			target->color = glm::vec3(1.0f, 0.2f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 1.0f);
			target++;

			target->position = glm::vec4(position.x - 0.5f * scale.x, position.y - 0.5f * scale.y, position.z, 1.0f);
			target->color = glm::vec3(0.2f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 0.0f);
			target++;

			target->position =glm::vec4(position.x + 0.5f * scale.x, position.y - 0.5f * scale.y, position.z, 1.0f);
			target->color = glm::vec3(0.2f, 0.2f, 1.0f);
			target->texcoord = glm::vec2(1.0f, 0.0f);
			target++;

			target->position = glm::vec4(position.x + 0.5f * scale.x, position.y + 0.5f * scale.y, position.z, 1.0f);
			target->color = glm::vec3(1.0f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(1.0f, 1.0f);
			target++;

			return target;
		}
	}
}

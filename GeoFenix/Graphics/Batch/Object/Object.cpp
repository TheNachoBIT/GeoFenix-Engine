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

		void RotateObject(Vertex& vert, glm::vec3 angle, glm::vec3 rotationCenter)
		{
			glm::mat4 One(1.0f);
			glm::mat4 translationMatrix;
			glm::mat4 rotationMatrix;
			glm::mat4 reverseTranslationMatrix;

			translationMatrix = glm::translate(One, -rotationCenter);
			rotationMatrix = glm::rotate(One, glm::radians(angle.x), glm::vec3(1.f, 0.f, 0.f));
			rotationMatrix = glm::rotate(One, glm::radians(angle.y), glm::vec3(0.f, 1.f, 0.f));
			rotationMatrix = glm::rotate(One, glm::radians(angle.z), glm::vec3(0.f, 0.f, 1.f));
			reverseTranslationMatrix = glm::translate(One, rotationCenter);

			vert.position = reverseTranslationMatrix* rotationMatrix* translationMatrix* glm::vec4(vert.position, 1.0f);
		}

		Vertex* Object::UpdateObject(Vertex* target)
		{
			float size = 1.0f;
			target->position = glm::vec3(position.x - 0.5f * scale.x, position.y + 0.5f * scale.y, position.z);
			target->color = glm::vec3(1.0f, 0.2f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 1.0f);
			RotateObject(*target,
				rotation,
				position);
			target++;

			target->position = glm::vec3(position.x - 0.5f * scale.x, position.y - 0.5f * scale.y, position.z);
			target->color = glm::vec3(0.2f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 0.0f);
			RotateObject(*target,
				rotation,
				position);
			target++;

			target->position = glm::vec3(position.x + 0.5f * scale.x, position.y - 0.5f * scale.y, position.z);
			target->color = glm::vec3(0.2f, 0.2f, 1.0f);
			target->texcoord = glm::vec2(1.0f, 0.0f);
			RotateObject(*target,
				rotation,
				position);
			target++;

			target->position = glm::vec3(position.x + 0.5f * scale.x, position.y + 0.5f * scale.y, position.z);
			target->color = glm::vec3(1.0f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(1.0f, 1.0f);
			RotateObject(*target,
				rotation,
				position);
			target++;

			return target;
		}
	}
}

#include "Object.h"

namespace geofenix
{
	namespace graphics
	{
		Object::Object(glm::vec3 pos, glm::vec3 sca)
		{
			position = pos;
			scale = sca;
		}

		Vertex* Object::UpdateObject(Vertex* target)
		{
			float size = 1.0f;
			target->position = glm::vec3(position.x - 0.5f, position.y + 0.5f, 0.0f);
			target->color = glm::vec3(1.0f, 0.2f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 1.0f);
			target++;

			target->position = glm::vec3(position.x - 0.5f, position.y - 0.5f, 0.0f);
			target->color = glm::vec3(0.2f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(0.0f, 0.0f);
			target++;

			target->position = glm::vec3(position.x + 0.5f, position.y - 0.5f, 0.0f);
			target->color = glm::vec3(0.2f, 0.2f, 1.0f);
			target->texcoord = glm::vec2(1.0f, 0.0f);
			target++;

			target->position = glm::vec3(position.x + 0.5f, position.y + 0.5f, 0.0f);
			target->color = glm::vec3(1.0f, 1.0f, 0.2f);
			target->texcoord = glm::vec2(1.0f, 1.0f);
			target++;

			return target;
		}
	}
}

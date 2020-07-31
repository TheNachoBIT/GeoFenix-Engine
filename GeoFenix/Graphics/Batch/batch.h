#pragma once

#include "Object\Object.h"

namespace geofenix
{
	namespace graphics
	{
		class Batch
		{
		public:
			Texture texture;

			GLuint VAO, VBO, EBO;

			std::vector<Object*> allObjects;
			glm::mat4 ModelMatrix;

			void StartVAO();
			void Matrix();
			void UpdateUniforms(Shader* shader);

			Batch(Texture& tex);
			~Batch();

			Object CreateObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);

			void Render(Shader* shader);
		};
	}
}

#pragma once

#include <thread>
#include "../Window/window.h"
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
			glm::mat4 ModelViewMatrix;

			Window& window;

			void StartVAO();
			void Matrix();
			void UpdateUniforms(Shader* shader);

			Batch(Texture& tex, Window& window);
			~Batch();

			Object CreateObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);
			bool inFrustum(glm::vec3 point3D);
			void AddObject(Object* obj);
			void PrintObjectList()
			{
				for (auto i : allObjects)
				{
					std::cout << i->position.x << ", " << i->position.y << ", " << i->position.z << std::endl;
				}
			}

			void Render(Shader* shader);
		};
	}
}

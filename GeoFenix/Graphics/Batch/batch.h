#pragma once

#include <thread>
#include "../Window/window.h"
#include "Object\Object.h"
#include "../Texture\texture.h"
#include <math.h>

namespace geofenix
{
	namespace graphics
	{
		class Batch
		{
		public:
			int batchID;

			Texture texture;

			GLuint VAO, VBO, EBO;

			std::vector<Object*> allObjects;
			glm::mat4 ModelMatrix;
			glm::mat4 ModelViewMatrix;

			Window& window;

			bool onStart = false;
			std::vector<uint32_t> indices;
			std::vector<Vertex> vertices;

			void StartVAO();
			void Matrix();
			void UpdateUniforms(Shader* shader);

			Batch(Texture& tex, Window& window, int id);
			~Batch();

			Object CreateObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);
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

#pragma once
#include <iostream>
#include <vector>

#include "GL/glew.h"
#include "glfw3.h"
#include "glm.hpp"

#include "../../Maths/vertex.h"
#include "../Shading/shader.h"
#include "../Texture/texture.h"

namespace geofenix
{
	namespace graphics
	{
		class Sprite
		{
		public:
			Texture texture;

			GLuint VAO, VBO, EBO;

			glm::vec3 position, rotation, scale;
			glm::mat4 ModelMatrix, ViewMatrix, ProjectionMatrix, LastModelMatrix;

			void StartVAO();
			void Matrix();
			void UpdateUniforms(Shader* shader);

			Sprite(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, Texture& tex);
			~Sprite();

			void Render(Shader* shader);
		};
	}
}

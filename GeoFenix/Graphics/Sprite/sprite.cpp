#include "sprite.h"

namespace geofenix
{
	namespace graphics
	{
		Vertex vertArray[] =
		{
			glm::vec3(-0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 0.2f, 0.2f),	glm::vec2(0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.2f, 1.0f, 0.2f),	glm::vec2(0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.2f, 0.2f, 1.0f),	glm::vec2(1.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.2f),	glm::vec2(1.0f, 1.0f),
		};

		unsigned numberOfVerts = sizeof(vertArray) / sizeof(Vertex);

		GLuint indArray[] =
		{
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7
		};

		unsigned numberOfIndices = sizeof(indArray) / sizeof(GLuint);

		Sprite::Sprite(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, Texture& tex) :
			position(pos), rotation(rot), scale(sca), texture(tex)
		{
			Sprite::StartVAO();
			Sprite::Matrix();
		}

		Sprite::~Sprite()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
		}

		void Sprite::StartVAO()
		{
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, numberOfVerts * sizeof(Vertex), vertArray, GL_STATIC_DRAW);

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), indArray, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);
		}

		void Sprite::Matrix()
		{
			ModelMatrix = glm::mat4(1.0f);
			ModelMatrix = glm::translate(ModelMatrix, position);
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			ModelMatrix = glm::scale(ModelMatrix, scale);
		}

		void Sprite::UpdateUniforms(Shader* shader)
		{
			shader->setUniform1i("texture0", 0);
			shader->setUniformMat4("ModelMatrix", ModelMatrix);
		}

		bool start = false;
		void Sprite::Render(Shader* shader)
		{
			Sprite::Matrix();

			Sprite::UpdateUniforms(shader);

			if (!start)
			{
				shader->enable();
				texture.enable(0);
				start = true;
			}

			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
		}
	}
}
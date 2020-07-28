#include "batch.h"

namespace geofenix
{
	namespace graphics
	{
		Batch::Batch(Texture& tex) :
			texture(tex)
		{
			
			Batch::StartVAO();
			Batch::Matrix();
		}

		Batch::~Batch()
		{
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
		}

		Object Batch::CreateObject(glm::vec3 pos, glm::vec3 sca)
		{
			Object obj(pos, sca);
			allObjects.push_back(&obj);
			return obj;
		}

		/*
		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			10, 11, 8
		};
		*/

		static const size_t MaxObjCount = 100000;
		static const size_t MaxVertexCount = MaxObjCount * 4;
		static const size_t MaxIndexCount = MaxObjCount * 6;
		static uint32_t indices[MaxObjCount * 6];

		void Batch::StartVAO()
		{

			glCreateVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			
			uint32_t offset = 0;
			for (size_t i = 0; i < MaxIndexCount; i += 6)
			{
				indices[i + 0] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;

				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;

				offset += 4;
			}

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
			glEnableVertexAttribArray(2);

			glBindVertexArray(0);
		}

		void Batch::Matrix()
		{
			ModelMatrix = glm::mat4(1.0f);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f));
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
			ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
			ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));
		}

		void Batch::UpdateUniforms(Shader* shader)
		{
			shader->setUniform1i("texture0", 0);
			shader->setUniformMat4("ModelMatrix", ModelMatrix);
		}

		static std::array<Vertex, MaxVertexCount> vertices;
		bool once = false;
		void Batch::Render(Shader* shader)
		{
			uint32_t indexCount = 0;

			//std::cout << sizeof(vertices) << std::endl;
			Vertex* buffer = vertices.data();

			for (int i = 0; i < allObjects.size(); i++)
			{
				buffer = allObjects[i]->UpdateObject(buffer);
				indexCount += 6;
			}

			Batch::Matrix();

			Batch::UpdateUniforms(shader);
			shader->enable();
			texture.enable(0);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		}
	}
}
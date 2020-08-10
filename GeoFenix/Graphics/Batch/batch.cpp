#include "batch.h"

namespace geofenix
{
	namespace graphics
	{
		Batch::Batch(Texture& tex, Window& window) :
			texture(tex), window(window)
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

		Object Batch::CreateObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
		{
			Object obj(pos, rot, sca);
			allObjects.push_back(&obj);
			return obj;
		}

		void Batch::AddObject(Object* obj)
		{
			allObjects.push_back(obj);
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

		void Batch::StartVAO()
		{

			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

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

		bool Batch::inFrustum(glm::vec3 point3D) {
			glm::vec4 clipSpacePos = window.ProjectionMatrix * (window.camera.ViewMatrix * glm::vec4(point3D, 0));
			std::cout << clipSpacePos.x << " " << clipSpacePos.y << std::endl;
			return clipSpacePos.x > -1 && clipSpacePos.x < 1 && clipSpacePos.z > -1 && clipSpacePos.z < 1;
		}


		static std::vector<uint32_t> indices;
		static std::vector<Vertex> vertices;
		bool once = false;
		void Batch::Render(Shader* shader)
		{
			uint32_t indexCount = 0;

			vertices.resize(allObjects.size() * 4);
			indices.resize(allObjects.size() * 6);

			Vertex* buffer = &vertices[0];

			for (int i = 0; i < allObjects.size(); i++)
			{
				buffer = allObjects[i]->UpdateObject(buffer);
				indexCount += 6;
			}

			Batch::UpdateUniforms(shader);

			if (!once)
			{
				shader->enable();
				texture.enable(0);
				once = true;
			}

			uint32_t offset = 0;
			for (size_t i = 0; i < allObjects.size() * 6; i += 6)
			{
				indices[i + 0] = 0 + offset;
				indices[i + 1] = 1 + offset;
				indices[i + 2] = 2 + offset;

				indices[i + 3] = 2 + offset;
				indices[i + 4] = 3 + offset;
				indices[i + 5] = 0 + offset;

				offset += 4;
			}

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, allObjects.size() * 4 * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, allObjects.size() * 6 * sizeof(uint32_t), &indices[0], GL_DYNAMIC_DRAW);

			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
		}
	}
}
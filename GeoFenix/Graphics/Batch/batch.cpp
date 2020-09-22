#include "batch.h"

namespace geofenix
{
	namespace graphics
	{
		Batch::Batch(Texture& tex, Window& window, int id) :
			texture(tex), window(window), batchID(id)
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

		bool comparePosition(Object* obj1, Object* obj2)
		{
			return (obj1->position.x < obj2->position.x);
		}

		Object Batch::CreateObject(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
		{
			Object obj(pos, rot, sca, batchID);
			allObjects.push_back(&obj);
			return obj;
		}

		void Batch::AddObject(Object* obj)
		{
			obj->id = batchID;
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

		std::vector<uint32_t> Batch::indices;
		std::vector<Vertex> Batch::vertices;

		void Batch::Render(Shader* shader)
		{
			uint32_t indexCount = 0;
			Vertex* buffer;

			vertices.resize(allObjects.size() * 4);
			if(allObjects.size() <= 5000)
				indices.resize(5000 * 6);
			else if(allObjects.size() > 5000)
				indices.resize(100000 * 6);

			if (!onStart)
			{
				std::cout << "Batch Info " << batchID << ": " << vertices.size() << " " << indices.size() << std::endl;

				shader->enable();
				texture.enable(0);

				onStart = true;
			}

			buffer = &vertices[0];

			for (auto i : allObjects)
			{
				buffer = i->UpdateObject(buffer);
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

			Batch::UpdateUniforms(shader);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_DYNAMIC_DRAW);
			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(uint32_t), indices.data());

			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, (indices.size() / 6) * 4, GL_UNSIGNED_INT, nullptr);
		}
	}
}
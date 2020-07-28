#pragma once
#include <GL/glew.h>
#include "glfw3.h"
#include "../../Maths/vertex.h"
#include "../../FileSystem/file.h"
#include "../../Graphics/Shading/shader.h"
#include "../../Graphics/Window/window.h"
#include "../../Graphics/Texture/texture.h"

using namespace geofenix;
using namespace graphics;

Vertex vertices[] =
{
	glm::vec3(-0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 0.2f, 0.2f),	glm::vec2(0.0f, 1.0f),
	glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(0.2f, 1.0f, 0.2f),	glm::vec2(0.0f, 0.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(0.2f, 0.2f, 1.0f),	glm::vec2(1.0f, 0.0f),
	glm::vec3(0.5f, 0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 0.2f),	glm::vec2(1.0f, 1.0f)
};

unsigned numberOfVerts = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] = 
{
	0, 1, 2,
	0, 2, 3
};

unsigned numberOfIndices = sizeof(indices) / sizeof(GLuint);
GLuint VAO;
GLuint VBO;
GLuint EBO;
GLuint texture0;
Shader shaderT;
Window win;

void SetTriangle()
{
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
glm::vec3 position(0.f);
glm::vec3 rotation(0.f);
glm::vec3 scale(1.f);

void Input()
{
	if (win.isKeyPressed(GLFW_KEY_Q))
		position.y += 0.005f;
	else if (win.isKeyPressed(GLFW_KEY_E))
		position.y -= 0.005f;

	if (win.isKeyPressed(GLFW_KEY_A))
		position.x -= 0.005f;
	else if (win.isKeyPressed(GLFW_KEY_D))
		position.x += 0.005f;

	if (win.isKeyPressed(GLFW_KEY_W))
		position.z -= 0.005f;
	else if (win.isKeyPressed(GLFW_KEY_S))
		position.z += 0.005f;

	if (win.isKeyPressed(GLFW_KEY_Z))
		rotation.y += 0.05f;
	else if (win.isKeyPressed(GLFW_KEY_X))
		rotation.y -= 0.05f;

	if (win.isKeyPressed(GLFW_KEY_C))
		rotation.z += 0.05f;
	else if (win.isKeyPressed(GLFW_KEY_V))
		rotation.z -= 0.05f;
}


void RenderTriangle(Texture &tex)
{
	glUseProgram(shaderT.prog);
	shaderT.setUniform1i("texture0", tex.textureUnit);

	Input();

	glm::mat4 ModelMatrix(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);

	glm::vec3 camPosition(0.f, 0.f, 2.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(win.frameBuff_Width) / win.frameBuff_Height, nearPlane, farPlane);

	shaderT.setUniformMat4("ModelMatrix", ModelMatrix);
	shaderT.setUniformMat4("ViewMatrix", ViewMatrix);
	shaderT.setUniformMat4("ProjectionMatrix", ProjectionMatrix);

	tex.enable();

	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, numberOfVerts);
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, 0);
}




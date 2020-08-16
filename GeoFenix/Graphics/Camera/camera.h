#pragma once

#include <iostream>

#include <GL/glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec3.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

enum direction {FORWARD, BACKWARD, LEFT, RIGHT};

namespace geofenix
{
	namespace graphics
	{
		class Camera
		{
		public:
			glm::mat4 ViewMatrix;
			glm::vec3 worldUp, position, front, right, up;
			GLfloat movementSpeed, sensitivity;
			GLfloat pitch, yaw, roll;

			Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
			~Camera();

			glm::vec4 planes[6];

			void CreateFrustumFromMatrix(const glm::mat4 matrix);

			float signedDistanceToPoint(glm::vec4 plane, glm::vec3 pt)
			{
				return glm::dot(glm::vec3(plane), pt) + plane.w;
			}

			bool pointIsInFrustum(glm::vec3 pt)
			{
				for (int i = 0; i < 6; i++)
				{
					if (signedDistanceToPoint(planes[i], pt) < 0)
					{
						return false;
					}
				}
				return true;
			}

			void UpdateCameraVectors();

			glm::mat4 UpdateViewMatrix();

			void MoveCamera(const float& deltaTime, const int direction);
			void Mouse(const float& deltaTime, const double& speedX, const double& speedY);
		};
	}
}

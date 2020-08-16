#include "camera.h"

namespace geofenix
{
	namespace graphics
	{
		Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp) :
			worldUp(worldUp), up(worldUp), position(position)
		{
			right = glm::vec3(0.f);

			ViewMatrix = glm::mat4(1.f);

			movementSpeed = 3.f;
			sensitivity = 5.f;

			pitch = 0.f;
			yaw = -90.f;
			roll = 0.f;

			UpdateCameraVectors();
		}

		Camera::~Camera()
		{

		}

		void Camera::CreateFrustumFromMatrix(const glm::mat4 matrix)
		{
			//left
			planes[0].x = matrix[0][3] + matrix[0][0];
			planes[0].y = matrix[1][3] + matrix[1][0];
			planes[0].z = matrix[2][3] + matrix[2][0];
			planes[0].w = matrix[3][3] + matrix[3][0];

			// right
			planes[1].x = matrix[0][3] - matrix[0][0];
			planes[1].y = matrix[1][3] - matrix[1][0];
			planes[1].z = matrix[2][3] - matrix[2][0];
			planes[1].w = matrix[3][3] - matrix[3][0];

			// bottom
			planes[2].x = matrix[0][3] + matrix[0][1];
			planes[2].y = matrix[1][3] + matrix[1][1];
			planes[2].z = matrix[2][3] + matrix[2][1];
			planes[2].w = matrix[3][3] + matrix[3][1];

			// top
			planes[3].x = matrix[0][3] - matrix[0][1];
			planes[3].y = matrix[1][3] - matrix[1][1];
			planes[3].z = matrix[2][3] - matrix[2][1];
			planes[3].w = matrix[3][3] - matrix[3][1];

			// near
			planes[4].x = matrix[0][3] + matrix[0][2];
			planes[4].y = matrix[1][3] + matrix[1][2];
			planes[4].z = matrix[2][3] + matrix[2][2];
			planes[4].w = matrix[3][3] + matrix[3][2];

			// far
			planes[5].x = matrix[0][3] - matrix[0][2];
			planes[5].y = matrix[1][3] - matrix[1][2];
			planes[5].z = matrix[2][3] - matrix[2][2];
			planes[5].w = matrix[3][3] - matrix[3][2];

			for (int i = 0; i < 6; i++)
			{
				float length = planes[i].length();
				planes[i] /= length;
			}
		}

		void Camera::UpdateCameraVectors()
		{
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			front = glm::normalize(front);
			right = glm::normalize(glm::cross(front, worldUp));
			up = glm::normalize(glm::cross(right, front));
		}

		glm::mat4 Camera::UpdateViewMatrix()
		{
			ViewMatrix = glm::lookAt(position, position + front, up);
			UpdateCameraVectors();
			return ViewMatrix;
		}

		void Camera::MoveCamera(const float& deltaTime, const int direction)
		{
			switch (direction)
			{
			case FORWARD:
				position += front * movementSpeed * deltaTime;
				break;
			case BACKWARD:
				position -= front * movementSpeed * deltaTime;
				break;
			case LEFT:
				position -= right * movementSpeed * deltaTime;
				break;
			case RIGHT:
				position += right * movementSpeed * deltaTime;
				break;
			default:
				break;
			}
		}

		void Camera::Mouse(const float& deltaTime, const double& speedX, const double& speedY)
		{
			pitch -= static_cast<GLfloat>(speedY) * sensitivity * deltaTime;
			yaw += static_cast<GLfloat>(speedX) * sensitivity * deltaTime;

			if (pitch > 80.f)
				pitch = 80.f;
			else if (pitch < -80.f)
				pitch = -80.f;

			if (yaw > 360.f || yaw < -360.f)
				yaw = 0.f;
		}
	}
}
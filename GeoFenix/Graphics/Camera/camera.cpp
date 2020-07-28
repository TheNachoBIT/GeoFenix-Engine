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
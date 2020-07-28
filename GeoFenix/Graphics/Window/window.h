#pragma once
#include <GL/glew.h>
#include <GL/GLU.h>
#include "glfw3.h"

#include "../../Objects/object2d.h"
#include "../Camera/camera.h"

#include "glm.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mat4x4.hpp"
#include "gtc/matrix_transform.hpp"

namespace geofenix {
	using namespace objects;
	namespace graphics {

#define KEYS		1024
#define MOUSE		32

		class Window {
		public:
			bool Initialize();
			static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
			static void CursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
			static void MouseState(GLFWwindow* window, unsigned int state);
		
			int m_Width, m_Height;
			static int frameBuff_Width, frameBuff_Height;
			const char *m_Name;
			GLFWwindow *m_Window;

			static bool keys[KEYS];
			static bool mouse[MOUSE];
			static double mouseX, mouseY, mouseSpeedX, mouseSpeedY;
			static bool fullScreen;

			Window(const char *name, int width, int height, bool fullscreen);
			~Window();
			void Update();
			bool Close();
			void Details();
			void Clear();

			bool isKeyPressed(unsigned int keycode);
			bool isMousePressed(unsigned int button);
			static void GetMousePosition(double& x, double& y);


			float deltaTime;
			void UpdateDeltaTime();
			
		private:
			float currentTime, lastTime;
			double lastMouseMoveX, lastMouseMoveY;
		public:


			//CAMERA PROPERTIES

			glm::mat4 ViewMatrix;
			glm::vec3 cameraPosition;
			glm::vec3 worldUp;
			glm::vec3 cameraFront;

			glm::mat4 ProjectionMatrix;
			float fov;
			float nearPlane;
			float farPlane;

			void InitMatrices();
			void RenderMatrix();

			//Shaders
			std::vector<Shader*> allShaders;

			//Textures
			std::vector<Texture*> allTextures;

			//Sprites
			std::vector<Sprite*> allSprites;

			//Objects
			std::vector<Object2D*> object2D;

			void InitComponents();

			void InitObjects();

			void Uniforms();

			void Render();

			void Input();

			Camera camera;

			Object2D* CreateObject(Object2D* obj);
		};

	}
}

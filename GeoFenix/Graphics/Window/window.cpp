#include "window.h"
#include <iostream>
#define PRINT(x) std::cout << x << std::endl;

namespace geofenix {
	namespace graphics {

		bool Window::keys[KEYS];
		bool Window::mouse[MOUSE];
		double Window::mouseX;
		double Window::mouseY;
		double Window::mouseSpeedX;
		double Window::mouseSpeedY;
		bool Window::fullScreen;
		int Window::frameBuff_Width, Window::frameBuff_Height;

		void Resize(GLFWwindow *window, int width, int height);

		Window::Window(const char *name, int width, int height, bool fullscreen) 
		 : camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
		{
			m_Name = name;
			m_Width = width;
			m_Height = height;
			fullScreen = fullscreen;

			if (!Initialize()) {
				std::cout << "Failed to open GLFW3 D:" << std::endl;
				//glfwTerminate();
			}

			for (int i = 0; i < KEYS; i++)
			{
				keys[i] = false;
			}

			for (int i = 0; i < MOUSE; i++)
			{
				mouse[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::Initialize() {
			if (!glfwInit()) {
				PRINT("Failed to open window :'c");
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

			if(!fullScreen)
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
			else
				m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, glfwGetPrimaryMonitor(), NULL);

			if (!m_Window) {
				PRINT("The Window didn't popped up :'(");
				//glfwTerminate();
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, Resize);
			glfwSetKeyCallback(m_Window, KeyCallback);
			glfwSetMouseButtonCallback(m_Window, MouseCallback);
			glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
			glfwGetFramebufferSize(m_Window, &frameBuff_Width, &frameBuff_Height);
			glfwSetFramebufferSizeCallback(m_Window, Resize);

			if (glewInit() != GLEW_OK) {
				PRINT("GLEW coudn't initialize! D:");
				return false;
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glClearColor(0.0, 0.0, 0.0, 1.0);

			InitComponents();
			InitObjects();
			InitMatrices();
			return true;
		}

		bool Window::Close() {
			return glfwWindowShouldClose(m_Window);
		}

		void Window::Update() {
			glfwPollEvents();

			UpdateDeltaTime();
			Uniforms();
			RenderMatrix();

			glfwSwapBuffers(m_Window);
		}

		void Window::Details() {
			PRINT("Started With Resolution:");
			PRINT("Width: " << m_Width << " Height: " << m_Height);
			PRINT("OpenGL " << glGetString(GL_VERSION));
		}

		void Window::Clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Resize(GLFWwindow *window, int width, int height) {
			glfwGetFramebufferSize(window, &Window::frameBuff_Width, &Window::frameBuff_Height);
			glViewport(0, 0, width, height);
		}

		void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->keys[key] = action != GLFW_RELEASE;
		}

		void Window::MouseCallback(GLFWwindow* window, int button, int action, int mods) {

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouse[button] = action != GLFW_RELEASE;
		}

		bool mouseStartUp = true;
		void Window::CursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseX = xPos;
			win->mouseY = yPos;
			
			if (mouseStartUp)
			{
				win->lastMouseMoveX = win->mouseX;
				win->lastMouseMoveY = win->mouseY;
				mouseStartUp = false;
			}

			win->mouseSpeedX = win->mouseX - win->lastMouseMoveX;
			win->mouseSpeedY = win->mouseY - win->lastMouseMoveY;

			if (win->mouseSpeedX < 5 && win->mouseSpeedX > -5)
				win->mouseSpeedX = 0;

			if (win->mouseSpeedY < 5 && win->mouseSpeedY > -5)
				win->mouseSpeedY = 0;

			win->lastMouseMoveX = win->mouseX;
			win->lastMouseMoveY = win->mouseY;
		}

		void Window::MouseState(GLFWwindow* window, unsigned int state)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glfwSetInputMode(window, GLFW_CURSOR, state);
		}

		bool Window::isKeyPressed(unsigned int keycode) {
			if (keycode >= KEYS)
			{
				return false;
			}

			return keys[keycode];
		}

		bool Window::isMousePressed(unsigned int button) {
			if (button >= MOUSE)
			{
				return false;
			}

			return mouse[button];
		}

		void Window::GetMousePosition(double& x, double& y) {
			x = mouseX;
			y = mouseY;
		}



		void Window::UpdateDeltaTime()
		{
			currentTime = static_cast<float>(glfwGetTime());
			deltaTime = currentTime - lastTime;
			lastTime = currentTime;
		}


		// Matrix Initialize

		void Window::InitMatrices()
		{
			cameraPosition = glm::vec3(0.f, 0.f, 2.f);
			worldUp = glm::vec3(0.f, 1.f, 0.f);
			cameraFront = glm::vec3(0.f, 0.f, -1.f);
			ViewMatrix = glm::mat4(1.f);
			ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, worldUp);

			fov = 90.f;
			nearPlane = 0.1f;
			farPlane = 1000.f;
			glm::mat4 ProjectionMatrix(1.f);
			ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBuff_Width) / frameBuff_Height, nearPlane, farPlane);
		}

		void Window::RenderMatrix()
		{
			ViewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraFront, worldUp);
			ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(frameBuff_Width) / frameBuff_Height, nearPlane, farPlane);
		}

		//Enable components
		void Window::InitComponents()
		{
			//Shaders
			allShaders.push_back(new Shader("Resources/Shaders/basic.vert", "Resources/Shaders/basic.frag", "Resources/Shaders/basicMinor.vert", "Resources/Shaders/basicMinor.frag"));

			//Textures
			allTextures.push_back(new Texture("Resources/Images/square.png", GL_TEXTURE_2D, 0, 200, 200));

			//Sprites
			allSprites.push_back(new Sprite(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f), *allTextures[0]));
		}

		void Window::InitObjects()
		{
			//CreateObject(new Object2D(glm::vec3(0.f), allTextures[0], allSprites));
		}

		void Window::Uniforms()
		{
			ViewMatrix = camera.UpdateViewMatrix();

			allShaders[0]->setUniformMat4("ViewMatrix", ViewMatrix);
			allShaders[0]->setUniformMat4("ProjectionMatrix", ProjectionMatrix);
		}

		void Window::Render()
		{
			for (int i = 0; i < object2D.size(); i++)
			{
				object2D[i]->Render(allShaders[0]);
			}
		}

		bool canMoveMouse = false;
		void Window::Input()
		{
			if(canMoveMouse)
				camera.Mouse(deltaTime, mouseSpeedX, mouseSpeedY);

			if (isKeyPressed(GLFW_KEY_W))
				camera.MoveCamera(deltaTime, FORWARD);
			if (isKeyPressed(GLFW_KEY_S))
				camera.MoveCamera(deltaTime, BACKWARD);
			if (isKeyPressed(GLFW_KEY_A))
				camera.MoveCamera(deltaTime, LEFT);
			if (isKeyPressed(GLFW_KEY_D))
				camera.MoveCamera(deltaTime, RIGHT);

			if (isKeyPressed(GLFW_KEY_LEFT_SHIFT))
				camera.movementSpeed = 6.f;
			else
				camera.movementSpeed = 3.f;

			if (isKeyPressed(GLFW_KEY_X))
			{
				MouseState(m_Window, GLFW_CURSOR_DISABLED);
				canMoveMouse = true;
			}
			if (isKeyPressed(GLFW_KEY_C))
			{
				MouseState(m_Window, GLFW_CURSOR_NORMAL);
				canMoveMouse = false;
			}
		}
		Object2D* Window::CreateObject(Object2D* obj)
		{
			object2D.push_back(obj);
			return obj;
		}
	}
}
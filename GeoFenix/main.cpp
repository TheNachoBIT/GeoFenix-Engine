#include <iostream>
#include "Game\Game.h"
//#include "Maths\vertex.h"
//#include "Resources\TestingScripts\rendertriangle.h"

using namespace geofenix;
using namespace graphics;

void setWindowFPS(GLFWwindow* win);

void Prnt()
{
	printf("Hello!");
}

void UpdateThread(Window& mainWindow)
{
	while (!mainWindow.Close())
	{
		mainWindow.Clear();
		//setWindowFPS(mainWindow.m_Window);

		mainWindow.Render();

		mainWindow.Input();

		Game::Update(mainWindow);

		mainWindow.Update();
	}
}

int main()
{
	Window mainWindow("GeoFenix Engine", 1280, 720, false);
	//win = mainWindow;
	//shaderT = shader;
	//SetTriangle();

	void Input(Window window, Sprite& sprite);

	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(mainWindow.m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImGui::StyleColorsDark();

	Game::Start(mainWindow);

	UpdateThread(mainWindow);
	
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	return 0;
}

double previousTime;
int frameCount;
void
setWindowFPS(GLFWwindow* win)
{
	double currentTime = glfwGetTime();
	frameCount++;
	// If a second has passed.
	if (currentTime - previousTime >= 1.0)
	{
		int positionX = rand() % 20;
		char title[128];
		snprintf(title, sizeof(title), "GeoFenix Engine || FPS: %d", frameCount);

 		glfwSetWindowTitle(win, title);

		frameCount = 0;
		previousTime = currentTime;
	}
}
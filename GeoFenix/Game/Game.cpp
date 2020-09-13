#include "Game.h"
namespace geofenix
{

	using namespace geodash;

	//Batch* batch;
	//Batch* batch2;
	Object* obj;
	std::vector<Batch*> allBatches;

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	int id;

	//This function gets called when the game starts
	void Game::Start(Window& window)
	{
		//Starts the batch that stores the objects

		/*
		Instantiate an object as an example, and make it into the "obj" pointer
		(you can do this without putting it a pointer and start the line with "new Object(..."
		if you don't wanna use it later on things like Update)
		*/

		//This is the system that loads the GD levels via GDBrowser
		id = File::ReadToInt("Resources/levelid.txt");
		Level::LoadInfo(id);
		//Level::Load(allBatches, id, window);

		//========================================================
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.SizePixels = 17;
		config.OversampleH = config.OversampleV = 1;
		config.PixelSnapH = true;
		io.Fonts->AddFontDefault(&config);
		//========================================================

		for (int i = 0; i < 5; i++)
		{
			allBatches.push_back(new Batch(*window.allTextures[0], window, i));
			for (int m = 0; m < 20; m++)
			{
				new Object(allBatches[i]->CreateObject(glm::vec3(i * 2, m, -m / 2), glm::vec3(0, 0, 45), glm::vec3(1)));
			}
		}

		//Gives information in the Console
		Details(window);
	}

	bool levelPropertiesWindow, renderingWindow;
	float renderLines[1000];
	int maxFPS = 1;

	//This function gets called per frame
	void Game::Update(Window& window)
	{
		Level::Render(allBatches, window);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::BeginMainMenuBar();
			if (ImGui::BeginMenu("Level"))
			{
				if (ImGui::MenuItem("Open from File")) { /* Do stuff */ }
				if (ImGui::MenuItem("Open from GDBrowser.com")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save As")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Level Properties")) { levelPropertiesWindow = true; }
				if (ImGui::MenuItem("Rendering and Performance")) { renderingWindow = true; }
				ImGui::EndMenu();
			}

			if (levelPropertiesWindow)
			{
				ImGui::Begin("Level Properties", &levelPropertiesWindow);
				ImGui::Text("Name: %s", Level::levelName);
				ImGui::Text("Made by: %s", Level::userName);
				ImGui::Text("ID: %i", id);
				ImGui::End();
			}

			if (renderingWindow)
			{
				ImGui::Begin("Rendering and Performance", &renderingWindow);
				ImGui::Text("Total Speed: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
				ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

				renderLines[999] = ImGui::GetIO().Framerate;

				for (int i = 0; i < 1000; i++)
				{
					if (i != 999)
					{
						renderLines[i] = renderLines[i + 1];
					}

					if (renderLines[i] > maxFPS)
						maxFPS = renderLines[i];
				}

				ImGui::PlotLines("", renderLines, 1000, 0, "", 1, maxFPS, ImVec2(ImGui::GetWindowWidth() - 15, 50));
				ImGui::End();
			}

			float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;

			float width = 450.f;
			float pos = width + ItemSpacing;

			if (!renderingWindow)
			{
				ImGui::SameLine(ImGui::GetWindowWidth() - pos);
				ImGui::Text("Engine performance >> %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			
			ImGui::EndMainMenuBar();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		

		//Render the objects in the batch per frame
		//batch->Render(window.allShaders[0]);
		//batch2->Render(window.allShaders[0]);

		//An example of Keyboard using Escape to quit the app
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}
	}
}

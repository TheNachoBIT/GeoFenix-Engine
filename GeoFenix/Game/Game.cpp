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
	static char idString[64] = "";
	int order;

	//This function gets called when the game starts
	void Game::Start(Window& window)
	{
		//Starts the batch that stores the objects

		/*
		Instantiate an object as an example, and make it into the "obj" pointer
		(you can do this without putting it a pointer and start the line with "new Object(..."
		if you don't wanna use it later on things like Update)
		*/

		//========================================================
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.SizePixels = 17;
		config.OversampleH = config.OversampleV = 1;
		config.PixelSnapH = true;
		io.Fonts->AddFontDefault(&config);
		//========================================================

		//This is the system that loads the GD levels via GDBrowser
		/*
		id = File::ReadToInt("Resources/levelid.txt");
		Level::LoadInfo(id);
		allBatches = Level::Load(id, window);
		*/

		//Gives information in the Console
		Details(window);
	}

	bool levelPropertiesWindow, renderingWindow, openGDBWindow = true, creditsWin, welcomeWin = true;
	float renderLines[1000];
	int maxFPS = 1;
	bool alreadyPressed;
	bool setDownloadMessage;

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
				if (ImGui::MenuItem("Open from GDBrowser.com")) { openGDBWindow = true; }
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
			if (ImGui::BeginMenu("Credits"))
			{
				creditsWin = true;
				ImGui::EndMenu();
			}

			if (welcomeWin)
			{
				ImGui::Begin("GeoFenix 0.2.0", &welcomeWin);
				ImGui::TextColored(ImVec4(0.3f, 1, 0.3f, 1), "Welcome to GEOFENIX!");
				ImGui::Text("");
				ImGui::TextColored(ImVec4(0.3f, 1, 0.3f, 1), "CONTROLS:");
				ImGui::Text("WASD: Move");
				ImGui::Text("X: Lock Mouse and Enable View Controls");
				ImGui::Text("C: Unlock Mouse and Disable View Controls");
				ImGui::Text("Mouse Movement: Control View");
				ImGui::End();
			}

			if (creditsWin)
			{
				ImGui::Begin("Credits", &creditsWin);
				ImGui::Text("Created and Developed by");
				ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "NachoBIT (https://twitter.com/TheNachoBIT)");
				ImGui::Text("");
				ImGui::Text("Web API coded by:");
				ImGui::TextColored(ImVec4(0, 1, 1, 1), "NicknameGG (https://twitter.com/NicknameGG_)");
				ImGui::Text("");
				ImGui::Text("Level Downloading supported by:");
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "GDBrowser (https://gdbrowser.com), ");
				ImGui::Text("which is made by: ");
				ImGui::TextColored(ImVec4(1, 0.6f, 0, 1), "GD Colon (https://twitter.com/TheRealGDColon)");
				ImGui::End();
			}

			if (setDownloadMessage && idString != "")
			{
				allBatches.clear();
				id = std::stoi(idString);
				std::cout << id << std::endl;
				allBatches = Level::Load(id, window);
				openGDBWindow = false;
				setDownloadMessage = false;
			}

			if (openGDBWindow)
			{
				ImGui::Begin("Open from Geometry Dash Servers (GDBrowser.com)", &openGDBWindow);
				ImGui::Text("Please type the level ID:");
				ImGui::InputText("", idString, 64);
				if (ImGui::Button("Open", ImVec2(100, 20)))
				{
					if(!setDownloadMessage)
					{
						ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Downloading and Loading Level...");
						ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "(See External Console for progress)");
						setDownloadMessage = true;
					}
				}
				ImGui::End();
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

				if (ImGui::GetIO().Framerate > 1000)
				{
					ImGui::TextColored(ImVec4(0, 1, 0.5f, 1), "Performance Quality: Extremely Good");
				}
				else if (ImGui::GetIO().Framerate > 500)
				{
					ImGui::TextColored(ImVec4(0, 1, 0.25f, 1), "Performance Quality: Really Good");
				}
				else if (ImGui::GetIO().Framerate > 240)
				{
					ImGui::TextColored(ImVec4(0, 1, 0.1f, 1), "Performance Quality: Very Good");
				}
				else if (ImGui::GetIO().Framerate > 60)
				{
					ImGui::TextColored(ImVec4(0, 1, 0, 1), "Performance Quality: Good");
				}
				else if (ImGui::GetIO().Framerate > 30)
				{
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "Performance Quality: Decent");
				}
				else if (ImGui::GetIO().Framerate > 15)
				{
					ImGui::TextColored(ImVec4(1, 0, 0, 1), "Performance Quality: Bad");
				}

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

				ImGui::Text("");
				ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Currently Rendering Per Frame:");
				ImGui::Text("Batches: %i", allBatches.size());

				int totalObjs = 0;
				for (auto i : allBatches)
				{
					totalObjs += i->allObjects.size();
				}

				ImGui::Text("Total Amount of Objects: %i", totalObjs);
				ImGui::Text("");
				ImGui::TextColored(ImVec4(1, 1, 0.2f, 1), "Application Specs:");
				ImGui::Text("Amount of cores available: %i", std::thread::hardware_concurrency());
				
				ImGui::End();
			}

			//ImGui::ShowDemoWindow();

			float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;

			float width = 450.f;
			float pos = width + ItemSpacing;

			if (!renderingWindow)
			{
				ImGui::SameLine(ImGui::GetWindowWidth() - pos);
				ImGui::Text("Engine performance >> %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			
			//ImGui::ShowDemoWindow();

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

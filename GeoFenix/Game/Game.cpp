#include "Game.h"
namespace geofenix
{

	using namespace geodash;

	//Object2D* obj;

	Batch* batch;
	Object* obj1, *obj2;

	//This function gets called when the game starts
	//===============================================
	void Game::Start(Window& window)
	{
		//Starts the batch that stores the objects
		batch = new Batch(*window.allTextures[0], window);
		/*
		This is an example of instantiating objects in the batch :D

		new Object(batch->CreateObject(glm::vec3(0, 0, 0), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f)));

		This is a for loop so you can do interesting stuff lol

		for(int x = 0; x < 100; x++)
			for (int y = 0; y < 100; y++)
			{
				new Object(batch->CreateObject(glm::vec3(x, y, 0), glm::vec3(0.f, 0.f, 45.f), glm::vec3(1.0f)));
			}
			*/

		//=============================================================
		//This is the system that loads the GD levels via GDBrowser
		int id;
		std::fstream stream("Resources/levelid.txt", std::ios::in);
		std::string result;

		if (stream.is_open())
		{
			getline(stream, result);
			id = std::stoi(result);
		}

		Level::Load(*batch, id);
		//==============================================================
		
		//Gives information in the Console
		Details(window);
	}

	//This function gets called per frame
	//====================================
	void Game::Update(Window& window)
	{
		//Render the objects in the batch per frame
		batch->Render(window.allShaders[0]);

		//An example of Keyboard using Escape to quit the app
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}
	}
}

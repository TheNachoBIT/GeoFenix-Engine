#include "Game.h"
namespace geofenix
{

	using namespace geodash;

	//Batch* batch;
	//Batch* batch2;
	Object* obj;
	std::vector<Batch*> allBatches;

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
		int id = File::ReadToInt("Resources/levelid.txt");
		Level::Load(allBatches, id, window);
		
		//Gives information in the Console
		Details(window);
	}

	//This function gets called per frame
	void Game::Update(Window& window)
	{
		//Render the objects in the batch per frame
		//batch->Render(window.allShaders[0]);
		//batch2->Render(window.allShaders[0]);
		Level::Render(allBatches, window);

		//An example of Keyboard using Escape to quit the app
		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}
	}
}

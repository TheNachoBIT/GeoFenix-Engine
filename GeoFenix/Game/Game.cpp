#include "Game.h"

namespace geofenix
{

	//Object2D* obj;

	Batch* batch;
	Object* obj1, *obj2;

	void Game::Start(Window& window)
	{
		Details(window);
		batch = new Batch(*window.allTextures[0]);
		for(int x = 0; x < 10; x++)
			for (int y = 0; y < 10; y++)
				new Object(batch->CreateObject(glm::vec3(x, y, 0.0f), glm::vec3(1.f)));
	}

	int frames = 0;
	bool done = false;
	void Game::Update(Window& window)
	{
		batch->Render(window.allShaders[0]);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}
	}
}

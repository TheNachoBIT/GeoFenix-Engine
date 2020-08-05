#include "Game.h"

namespace geofenix
{

	using namespace geodash;

	//Object2D* obj;

	Batch* batch;
	Object* obj1, *obj2;

	void Game::Start(Window& window)
	{
		Details(window);
		batch = new Batch(*window.allTextures[0]);
		/*
		for(int x = 0; x < 100; x++)
			for (int y = 0; y < 100; y++)
			{
				new Object(batch->CreateObject(glm::vec3(x, y, 0), glm::vec3(0.f, 0.f, 45.f), glm::vec3(1.0f)));
			}
			*/

		Level::Load(*batch, 0);

		/*



		Nickname, Te comente esto para que no rompa los huevos la consola perdon x'd

		std::string pija;
		geofenix::web::get("www.google.com", pija);
		std::cout << pija;
		*/
	}



	void SayHello()
	{
		printf("Hello! \n");
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

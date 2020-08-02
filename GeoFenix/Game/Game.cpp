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
			{
				new Object(batch->CreateObject(glm::vec3(x, y, 0), glm::vec3(0.f, 0.f, x + y * 10.0f), glm::vec3(1.0f)));
			}

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

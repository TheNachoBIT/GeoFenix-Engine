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
		new Object(batch->CreateObject(glm::vec3(0, 0, 0), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f)));
		new Object(batch->CreateObject(glm::vec3(1, 0, 0), glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.0f)));

		/*

		Nickname, Te comente esto para que no rompa los huevos la consola perdon x'd

		std::string pija;
		geofenix::web::get("www.google.com", pija);
		std::cout << pija;
		*/
	}


	int frames = 0;
	bool done = false;
	void Game::Update(Window& window)
	{
		batch->Render(window.allShaders[0]);

		batch->allObjects[1]->rotation.z += 0.05f;

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
		{
			exit(0);
		}
	}
}

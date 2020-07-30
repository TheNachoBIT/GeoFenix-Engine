#pragma once
#include <iostream>
#include "../Graphics/Window/window.h"
#include "../Graphics/Batch/batch.h"
#include "../Web/web.h"
#define Print(x) std::cout << x << std::endl;

namespace geofenix
{
	using namespace graphics;

	static class Game
	{
	public:
		static void Start(Window& window);
		static void Update(Window& window);

		static void Details(Window& window)
		{
			Print("======================================");
			Print("");
			Print("Welcome to GeoFenix!");
			Print("Current Resolution: " << window.m_Width << " x " << window.m_Height);
			Print("");
			Print("Created by NachoBIT (twitter.com/TheNachoBIT)");
			Print("TEST BUILD 0.01");
			Print("");
			Print("CONTROLS:");
			Print("WASD: Move");
			Print("X: Lock Mouse and Enable View Controls");
			Print("C: Unlock Mouse and Disable View Controls");
			Print("Mouse Movement: Control View");
			Print("");
			Print("EXPERIMENTS YOU CAN DO:");
			Print("The shaders of the engine can be easily modified, if you go to Resources/Shaders/");
			Print("You can change the way the square is being draw in the scene via basic.vert and basic.frag!");
			Print("In the case of a syntax error while modifying, it will drop an error at the top of this whole message.");
			Print("");
			Print("This is still at the moment Close Source due to being an unfinished product.");
			Print("But feel free to look at the code (if you can) and if you are a programmer,");
			Print("Let me know if i'm doing something that is not that great, i'm open to criticism :)");
			Print("");
			Print("======================================");
		}
	};
}

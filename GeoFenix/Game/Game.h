#pragma once
#include <iostream>
#include "../Graphics/Window/window.h"
#include "../Graphics/Batch/batch.h"
#include "../Web/web.h"
#include <thread>
#include "../FileSystem/file.h"
#define Print(x) std::cout << x << std::endl;

#include "../Geometry Dash/gd.h"

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
			Print("Amount of cores: " << std::thread::hardware_concurrency());
			Print("");
			Print("Created and Developed by NachoBIT (https://twitter.com/TheNachoBIT)");
			Print("Web API by NicknameGG (https://twitter.com/NicknameGG_)");
			Print("Level Downloading supported by GDBrowser (https://gdbrowser.com), made by Colon (https://twitter.com/TheRealGDColon)");
			Print("");
			Print("TEST BUILD 0.10");
			Print("");
			Print("CONTROLS:");
			Print("WASD: Move");
			Print("X: Lock Mouse and Enable View Controls");
			Print("C: Unlock Mouse and Disable View Controls");
			Print("Mouse Movement: Control View");
			Print("");
			Print("HOW TO LOAD A DIFFERENT LEVEL");
			Print("================================");
			Print("If you go to the 'Resources' folder, you'll see a text file called 'levelid.txt'.");
			Print("If you open it, you'll see a level ID stored in there, that's the level that is gonna load in the app.");
			Print("To load another level, you simply copy the ID you want from GD (or GDBrowser) and replace the ID in the");
			Print("text file with the one that you copied. After that, you restart the application.");
			Print("================================");
			Print("");
			Print("EXPERIMENTS YOU CAN DO:");
			Print("================================");
			Print("The shaders of the engine can be easily modified, if you go to Resources/Shaders/");
			Print("You can change the way the square is being draw in the scene via basic.vert and basic.frag!");
			Print("basicMinor.vert and basicMinor.frag are the same but for older processors and graphics cards.");
			Print("In the case of a syntax error while modifying, it will drop an error at the top of this whole message.");
			Print("================================");
			Print("");
			Print("This is still at the moment Close Source due to being an unfinished product.");
			Print("But feel free to look at the code (if you can) and if you are a programmer,");
			Print("Let me know if i'm doing something that is not that great, i'm open to criticism :)");
			Print("");
			Print("======================================");
		}
	};
}

#pragma once
#include <iostream>

//include "../Graphics/Window/window.h"
//include "../Graphics/Batch/batch.h"
//include "../Web/web.h"
//include <thread>
//#include "../FileSystem/file.h"
#define Print(x) std::cout << x << std::endl;

#include "../Geometry Dash/gd.h"

#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_glfw.h"
#include "../ImGUI/imgui_impl_opengl3.h"
#include "../ImGUI/imgui_internal.h"

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
			Print("TEST BUILD 0.2.0");
			Print("");
			Print("EXPERIMENTS YOU CAN DO:");
			Print("================================");
			Print("The shaders of the engine can be easily modified, if you go to Resources/Shaders/");
			Print("You can change the way the square is being draw in the scene via basic.vert and basic.frag!");
			Print("basicMinor.vert and basicMinor.frag are the same but for older processors and graphics cards.");
			Print("In the case of a syntax error while modifying, it will drop an error at the top of this whole message.");
			Print("================================");
			Print("======================================");
		}
	};
}

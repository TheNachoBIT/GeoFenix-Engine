#pragma once
#include <string>
#include <SOIL2.h>

namespace geofenix
{
	class File
	{
	public:
		static std::string Read(const char* filePath)
		{
			FILE* file = fopen(filePath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}

		static int ReadToInt(const char* filePath)
		{
			std::string result = Read(filePath);
			return std::stoi(result);
		}

		static unsigned char* LoadImage(const char* filePath, int image_width, int image_height)
		{
			unsigned char* image = SOIL_load_image(filePath, &image_width, &image_height, NULL, SOIL_LOAD_RGBA);
			return image;
		}
	};
}

#pragma once

#include "../Graphics/Batch/batch.h"
#include <fstream>
#include <string.h>
#include "../Web/web.h";

namespace geodash
{
	using namespace geofenix;
	using namespace graphics;
	static class Level
	{
	public:
		static std::vector<std::string>* loadedObjects;
		static void Load(Batch& batch, int id);

		static std::vector<std::string> GetAllObjects(const std::string& ret);
		static void GetObjectProperties(int id, Batch& batch);

		static void Split(std::vector<std::string>& v, const std::string& s, const char* c
		) {
			std::string::size_type i = 0;
			std::string::size_type j = s.find(c);

			while (j != std::string::npos) {
				v.push_back(s.substr(i, j - i));
				i = ++j;
				j = s.find(c, j);

				if (j == std::string::npos)
					v.push_back(s.substr(i, s.length()));
			}
		};
	};
}
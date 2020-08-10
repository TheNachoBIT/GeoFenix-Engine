#include "gd.h"
namespace geodash
{
	using namespace web;

	std::vector<std::string>* Level::loadedObjects;

	void Level::Load(Batch& batch, int id)

	{
		std::string theresp;
		std::string web = "https://gdbrowser.com/api/analyze/" + std::to_string(id);

		std::string theresp2;
		std::string web2 = "https://gdbrowser.com/api/level/" + std::to_string(id) + "?download=true";

		web::get(web.c_str(), theresp, true);

		if (theresp != "-1")
		{
			std::cout << "GDBrowser: Level Analyzer not corrupted!" << std::endl;
			auto text = nlohmann::json::parse(theresp);

			if (text["data"] != "")
			{
				loadedObjects = new std::vector<std::string>(Level::GetAllObjects(text["data"]));
				for (int i = 0; i < loadedObjects->size(); i++)
				{
					GetObjectProperties(i, batch);
				}
			}
			else
				std::cout << "ERROR: Txt file not found." << std::endl;
		}
		else
		{
			std::cout << "GDBrowser: Level Analyzer data corrupted! Retrieving Normal Level data..." << std::endl;
			web::get(web2.c_str(), theresp2, true);

			if (theresp2 != "-1")
			{
				std::cout << "GDBrowser: Normal Level data not corrupted!" << std::endl;
				auto text2 = nlohmann::json::parse(theresp2);

				if (text2["data"] != "")
				{
					loadedObjects = new std::vector<std::string>(Level::GetAllObjects(text2["data"]));
					for (int i = 0; i < loadedObjects->size(); i++)
					{
						GetObjectProperties(i, batch);
					}
				}
				else
					std::cout << "ERROR: Txt file not found." << std::endl;
			}
			else
				std::cout << "ERROR: Returns -1" << std::endl;
		}
	}

	std::vector<std::string> Level::GetAllObjects(const std::string& ret)
	{
		std::vector<std::string> objs;
		Level::Split(objs, ret, ";");
		//No colors so for now we delete the first part
		objs.erase(objs.begin());
		objs.pop_back();

		std::cout << "Objects Splitted!" << std::endl;

		return objs;
	}

	void Level::GetObjectProperties(int id, Batch& batch)
	{
		std::vector<std::string> splitProcess;
		Level::Split(splitProcess, loadedObjects->at(id), ",");
		std::vector<int> variables;
		std::vector<std::string> results;

		for (int i = 0; i < splitProcess.size(); i++)
		{
			if (i % 2 == 0)
			{
				variables.push_back(std::stoi(splitProcess[i]));
			}
			else
				results.push_back(splitProcess[i]);
		}

		glm::vec3 position(0.f), rotation(0.f), scale(1.0f);
		for (int i = 0; i < variables.size(); i++)
		{
			switch (variables[i])
			{
			//Object ID
			case 1:
				break;

			//Position
			case 2:
				position.x = std::stoi(results[i]) / 30;
				break;
			case 3:
				position.y = std::stoi(results[i]) / 30;
				break;

			//Rotation
			case 6:
				rotation.z = -std::stoi(results[i]);
				break;

			//Scale (GD)
			case 32:
				scale.x = std::stoi(results[i]);
				scale.y = std::stoi(results[i]);
				break;
			}
		}

		new Object(batch.CreateObject(position, rotation, scale));
	}
}
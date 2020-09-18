#include "gd.h"
namespace geodash
{
	using namespace web;

	std::vector<std::string>* Level::loadedObjects;
	Batch* currentBatch;

	void Remove(std::vector<int>& v)
	{
		auto end = v.end();
		for (auto it = v.begin(); it != end; ++it) {
			end = std::remove(it + 1, end, *it);
		}

		v.erase(end, v.end());
	}

	std::vector<Batch*> Level::Load(int id, Window& window)
	{
		std::vector<Batch*> batches;
		std::vector<Object*> loadedObjs;
		std::vector<int> batchIDs;

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
					Object* obj = new Object(GetObjectProperties(i));
					loadedObjs.push_back(obj);
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
						Object* obj = new Object(GetObjectProperties(i));
						loadedObjs.push_back(obj);
					}
				}
				else
					std::cout << "ERROR: Txt file not found." << std::endl;
			}
			else
				std::cout << "ERROR: Returns -1" << std::endl;
		}

		for (auto i : loadedObjs)
		{
			batchIDs.push_back(i->id);
		}

		Remove(batchIDs);

		for (auto m : batchIDs)
		{
			batches.push_back(new Batch(*window.allTextures[0], window, m));
		}

		for (auto i : loadedObjs)
		{
			for (auto m : batches)
			{
				if (i->id == m->batchID)
				{
					m->AddObject(i);
				}
			}
		}

		return batches;
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

	int Level::GetObjectID(int id)
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
		int objectID = 0;
		glm::vec3 position(0.f), rotation(0.f), scale(1.0f);
		for (int i = 0; i < variables.size(); i++)
		{
			switch (variables[i])
			{
				//Object ID
			case 1:
				return std::stoi(results[i]);
			}
		}
	}

	Object Level::GetObjectProperties(int id)
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
		int objectID = 0;
		glm::vec3 position(0.f), rotation(0.f), scale(1.0f);
		for (int i = 0; i < variables.size(); i++)
		{
			switch (variables[i])
			{
			//Object ID
			case 1:
				objectID = std::stoi(results[i]);
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
				if(scale.x != 0 && scale.y != 0)
				{
				scale.x = std::stoi(results[i]);
				scale.y = std::stoi(results[i]);
				}
				break;
			}
		}

		return Object(position, rotation, scale, objectID);
	}

	void Level::Render(std::vector<Batch*>& batches, Window& window)
	{
		for (auto m : batches)
		{
			m->Render(window.allShaders[0]);
		}
	}

	std::string Level::levelName;
	std::string Level::userName;

	void Level::LoadInfo(int id)
	{
		std::string resp;
		std::string web = "https://gdbrowser.com/api/level/" + std::to_string(id);
		web::get(web.c_str(), resp, false);
		auto jsonText = nlohmann::json::parse(resp);
		levelName = jsonText["name"];
		userName = jsonText["author"];
	}
}
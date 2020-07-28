#include "object2d.h"

namespace geofenix
{
	using namespace graphics;
	namespace objects
	{
		Object2D::Object2D(const char* name, glm::vec3 position, Texture * tex, std::vector<Sprite*> spritesToAdd) :
			position(position), texture(tex), name(name)
		{
			rotation = glm::vec3(0.f);
			scale = glm::vec3(1.f);
			for (auto*i : spritesToAdd)
			{
				sprites.push_back(new Sprite(*i));
			}
		}

		Object2D::~Object2D()
		{
			for (auto*& i : sprites)
			{
				delete i;
			}
		}

		void Object2D::Update()
		{

		}

		void Object2D::Render(Shader *shader)
		{
			for (auto& i : sprites)
			{
				i->Render(shader);
				i->position = position;
				i->rotation = rotation;
				i->scale = scale;
			}
		}
	}
}
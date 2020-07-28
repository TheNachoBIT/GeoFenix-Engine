#pragma once

#include "../Graphics/Sprite/sprite.h"
#include "../Graphics/Texture/texture.h"
#include "../Graphics/Shading/shader.h"

namespace geofenix
{
	using namespace graphics;
	namespace objects
	{
		class Object2D
		{
		public:
			const char* name;
			std::vector<Sprite*> sprites;
			Texture* texture;
			glm::vec3 position, rotation, scale;

			Object2D(const char* name, glm::vec3 position, Texture* tex, std::vector<Sprite*> spritesToAdd);
			~Object2D();

			void Update();
			void Render(Shader *shader);
		};
	}
}
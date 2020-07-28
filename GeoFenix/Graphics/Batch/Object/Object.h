#pragma once

#include <vector>
#include <iostream>
#include <array>
#include "../../Shading/shader.h"
#include "../../Texture/texture.h"
#include "../../../Maths/vertex.h"

namespace geofenix
{
	namespace graphics
	{
		class Object
		{
		public:
			glm::vec3 position;
			glm::vec3 scale;

			Object(glm::vec3 pos, glm::vec3 sca);

			Vertex* UpdateObject(Vertex* target);
		};
	}
}

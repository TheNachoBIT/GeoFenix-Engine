#pragma once

#include <vector>
#include <iostream>
#include <array>
#include "../../Shading/shader.h"
#include "../../Texture/texture.h"
#include "../../../Maths/vertex.h"
#include "gtx/quaternion.hpp"
#include "glm.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include "math.h"

namespace geofenix
{
	namespace graphics
	{
		class Object
		{
		public:
			int id;

			glm::vec3 position;
			glm::vec3 lastPosition;
			glm::vec3 rotation;
			glm::vec3 lastRotation;
			glm::vec3 scale;
			std::vector<Object*> neighbours;
			bool isVisible = true;
			bool onStart = false;

			Object(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca, int ObjId);

			glm::mat4 translationMatrix, rotationMatrix;

			Vertex* UpdateObject(Vertex* target);
		};
	}
}

#pragma once
#include "glm.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
struct Vertex
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
};

#pragma once

#include <vector>

#include "glm/glm.hpp"

struct Sphere
{
	glm::vec3 Center = {0.0, 0.0, 0.0};
	float Radius = 0.5;
	glm::vec3 Color = {0.0, 0.0, 0.0};
};

struct Scene
{
	std::vector<Sphere> spheres;
};
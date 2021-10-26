#pragma once
#include "Geometry.h"

class Triangle : public Geometry
{
public:
	Triangle() = default;
	Triangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3) :
		v1{ v1 },
		v2{ v2 },
		v3{ v3 }
	{
	}

	//bool Hit(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit) override;

public:
	glm::vec3 v1{ 0, 0, 0 };
	glm::vec3 v2{ 0, 0, 0 };
	glm::vec3 v3{ 0, 0, 0 };
};


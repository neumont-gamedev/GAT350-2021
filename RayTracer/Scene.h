#pragma once
#include "Types.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"

#include <memory>
#include <vector>

class Scene
{
public:
	glm::vec3 Trace(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit, int depth);
	void Add(std::unique_ptr<Geometry> geometry);

protected:
	std::vector<std::unique_ptr<Geometry>> objects;
};

#include "Plane.h"

bool Plane::Hit(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit)
{
    float denominator = glm::dot(ray.direction, normal);

    if (abs(denominator) < glm::epsilon<float>())
    {
        return false; // direction and plane parallel, no intersection
    }

    float t = glm::dot(center - ray.origin, normal) / denominator;
    if (t < 0)
    {
        return false; // ray origin is behind the plane (backside of the plane)
    }

    if (t >= tMin && t <= tMax)
    {
        hit.t = t;
        hit.point = ray.pointAt(t);
        hit.normal = normal;
        hit.material = material.get();

        return true;
    }

    return false;
}
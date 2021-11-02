#pragma once
#include "Types.h"

class Sampler
{
public:
	virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const = 0;
};

class ColorSampler : public Sampler {
public:
    ColorSampler() = default;
    ColorSampler(const glm::vec3& color) : color{ color } {}

    virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const override 
    {
        return color;
    }

public:
    glm::vec3 color;
};

class CheckerSampler : public Sampler {
public:
    CheckerSampler() = default;
    CheckerSampler(std::shared_ptr<Sampler> even, std::shared_ptr<Sampler> odd)
        : even{ even }, odd{ odd }
    {}

    CheckerSampler(const glm::vec3& color1, const glm::vec3& color2)
        : even(std::make_shared<ColorSampler>(color1)), odd(std::make_shared<ColorSampler>(color2)) {}

    virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const override 
    {
        auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
        return (sines < 0) ? odd->value(uv, p) : even->value(uv, p);
    }

public:
    std::shared_ptr<Sampler> odd;
    std::shared_ptr<Sampler> even;
};

class TextureSampler : public Sampler {
public:
    TextureSampler() = default;

    virtual glm::vec3 value(const glm::vec2& uv, const glm::vec3& p) const override
    {
        return glm::vec3{ 0, 1, 1 };
    }
};
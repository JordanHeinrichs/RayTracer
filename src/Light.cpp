#include "Light.h"

Light::Light(
    const Point3D position,
    const Color& diffuse,
    const Color& specular)
: position_(position)
, diffuse_(diffuse)
, specular_(specular)
{
}

Light::~Light()
{
}

const Point3D& Light::position() const
{
    return position_;
}

Color Light::diffuse() const
{
    return diffuse_;
}

Color Light::specular() const
{
    return specular_;
}


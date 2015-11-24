#include "Material.h"

Material::Material(const Color& color,
    double shininess)
: specular_(color)
, diffuse_(color)
, ambient_(color)
, shininess_(shininess)
{
}

Material::Material(const Color& specular,
    const Color& diffuse,
    const Color& ambient,
    double shininess)
: specular_(specular)
, diffuse_(diffuse)
, ambient_(ambient)
, shininess_(shininess)
{
}

Material::~Material()
{
}

Color Material::specular() const
{
    return specular_;
}

Color Material::diffuse() const
{
    return diffuse_;
}

Color Material::ambient() const
{
    return ambient_;
}

double Material::shininess() const
{
    return shininess_;
}

#pragma once

#include "algebra.h"

class Material
{
public:
    Material();
    Material(const Color& color,
        double shininess);
    Material(const Color& specular,
        const Color& diffuse,
        const Color& ambient,
        double shininess);
    virtual ~Material();

    Color specular() const;
    Color diffuse() const;
    Color ambient() const;
    double shininess() const;

private:
    Color specular_;
    Color diffuse_;
    Color ambient_;
    double shininess_;
};

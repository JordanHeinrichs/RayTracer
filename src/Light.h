#pragma once

#include "algebra.h"

class Light
{
public:
    Light(const Point3D position,
        const Color& diffuse,
        const Color& specular);
    virtual ~Light();

    const Point3D& position() const;
    Color diffuse() const;
    Color specular() const;

private:
    Point3D position_;
    Color diffuse_;
    Color specular_;
};

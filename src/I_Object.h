#pragma once

#include "algebra.h"
class IntersectionMatch;
class Material;
class Ray;

class I_Object
{
public:
    virtual ~I_Object() {}

    virtual IntersectionMatch doesRayIntersect(const Ray& ray) const = 0;

    virtual Vector4D normal(const Vector4D& point) const = 0;
    virtual const Material& material() const = 0;
};

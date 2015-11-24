#pragma once

#include "algebra.h"
class Ray;
class Material;

class I_Object
{
public:
    virtual ~I_Object() {}

    virtual bool doesRayIntersect(const Ray& ray, double& t) const = 0;

    virtual Vector4D normal(const Vector4D& point) const = 0;
    virtual const Material& material() const = 0;
};

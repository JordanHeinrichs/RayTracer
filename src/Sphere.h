#pragma once

#include "I_Object.h"
#include "Material.h"
class Ray;

class Sphere : public I_Object
{
public:
    Sphere(const Point3D& center, double radius, const Material& material);
    virtual ~Sphere();

    IntersectionMatch doesRayIntersect(const Ray& ray) const;
    Vector4D normal(const Vector4D& point) const;
    const Material& material() const;

private:
    Vector4D center_;
    double radius_;
    const Material material_;
};

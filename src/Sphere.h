#pragma once

#include "I_Object.h"
class Ray;

class Sphere : public I_Object
{
public:
    Sphere(const Point3D& center, double radius);
    virtual ~Sphere();

    bool doesRayIntersects(const Ray& ray) const;

private:
    Vector4D center_;
    double radius_;
};

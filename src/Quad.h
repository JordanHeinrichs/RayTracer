#pragma once

#include "I_Object.h"
#include "Material.h"
#include "Triangle.h"
class Ray;

class Quad : public I_Object
{
public:
    Quad(const Point3D& point1,
        const Point3D& point2,
        const Point3D& point3,
        const Point3D& point4,
        const Material& material);
    virtual ~Quad();

    IntersectionMatch doesRayIntersect(const Ray& ray) const;
    Vector4D normal(const Vector4D& point) const;
    const Material& material() const;

private:
    const Triangle tri1_;
    const Triangle tri2_;
};

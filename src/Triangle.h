#pragma once

#include "I_Object.h"
#include "Material.h"
class Ray;

class Triangle : public I_Object
{
public:
    Triangle(const Point3D& point1, const Point3D& point2, const Point3D& point3, const Material& material);
    virtual ~Triangle();

    bool doesRayIntersect(const Ray& ray, double& t) const;
    Vector4D normal(const Vector4D& point) const;
    const Material& material() const;

private:
    const Point3D point1_;
    const Point3D point2_;
    const Point3D point3_;
    const Material material_;
};

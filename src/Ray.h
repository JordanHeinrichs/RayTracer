#pragma once
#include "algebra.h"

class Ray
{
public:
    Ray(const Point3D& startPoint, const Vector4D& directionVector);
    Ray(const Point3D& startPoint, const Point3D& pointAlongRay);
    virtual ~Ray();

    Point3D startPoint() const;
    Vector4D directionVector() const;
    Point3D pointAlongRay(double t) const;

private:
    const Point3D startPoint_;
    Vector4D directionVector_;
};

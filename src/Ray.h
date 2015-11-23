#pragma once
#include "algebra.h"

class Ray
{
public:
    Ray(const Point3D& startPoint, const Vector4D& directionVector);
    Ray(const Point3D& startPoint, const Point3D& pointAlongLine);
    virtual ~Ray();

    Vector4D startPoint() const;
    Vector4D directionVector() const;

private:
    const Vector4D startPoint_;
    Vector4D directionVector_;
};

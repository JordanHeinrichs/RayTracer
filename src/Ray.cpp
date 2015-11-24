#include "Ray.h"

Ray::Ray(const Point3D& startPoint, const Vector4D& directionVector)
: startPoint_(startPoint)
, directionVector_(directionVector)
{
}

Ray::Ray(const Point3D& startPoint, const Point3D& pointAlongRay)
: startPoint_(startPoint)
{
    Vector4D directionalVector = pointAlongRay - startPoint;
    directionalVector.normalize();
    directionVector_ = directionalVector;
}

Ray::~Ray()
{
}

Point3D Ray::startPoint() const
{
    return startPoint_;
}

Vector4D Ray::directionVector() const
{
    return directionVector_;
}

Point3D Ray::pointAlongRay(double t) const
{
    return (Vector4D(startPoint_) + (t * directionVector_)).toPoint();
}

#include "Ray.h"

Ray::Ray(const Point3D& startPoint, const Vector4D& directionVector)
: startPoint_(startPoint)
, directionVector_(directionVector)
{
}

Ray::Ray(const Point3D& startPoint, const Point3D& pointAlongLine)
: startPoint_(startPoint)
{
    Vector4D directionalVector = pointAlongLine - startPoint;
    directionalVector.normalize();
    directionVector_ = directionalVector;
}

Ray::~Ray()
{
}

Vector4D Ray::startPoint() const
{
    return startPoint_;
}

Vector4D Ray::directionVector() const
{
    return directionVector_;
}

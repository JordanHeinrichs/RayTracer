#include <cmath>
#include "IntersectionMatch.h"
#include "Ray.h"
#include "Sphere.h"

Sphere::Sphere(const Point3D& center, double radius, const Material& material)
: center_(center)
, radius_(radius)
, material_(material)
{
}

Sphere::~Sphere()
{
}

IntersectionMatch Sphere::doesRayIntersect(const Ray& ray) const
{
    Vector4D D = Vector4D(ray.startPoint()) - center_;
    double a = 1.0;
    double b = 2.0 * (ray.directionVector().dot(D));
    double c = D.dot(D) - std::pow(radius_, 2);
    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
    {
        return IntersectionMatch();
    }
    double t1 = (-b + std::sqrt(discriminant)) / 2.0;
    double t2 = (-b - std::sqrt(discriminant)) / 2.0;

    if (t1 > 0 && t1 < t2)
    {
        return IntersectionMatch(true, this, t1);
    }
    else if (t2 > 0)
    {
        return IntersectionMatch(true, this, t2);
    }
    else
    {
        return IntersectionMatch();
    }
}

Vector4D Sphere::normal(const Vector4D& point) const
{
    Vector4D normal(point - center_);
    normal.normalize();
    return normal;
}

const Material& Sphere::material() const
{
    return material_;
}

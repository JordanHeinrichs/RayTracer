#include <cmath>
#include "Ray.h"
#include "Sphere.h"

Sphere::Sphere(const Point3D& center, double radius)
: center_(center)
, radius_(radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::doesRayIntersects(const Ray& ray) const
{
    // D is the ray from the startPoint to the center of the sphere
    Vector4D D = center_ - ray.startPoint();
    double a = 1.0;
    double b = 2.0 * (ray.directionVector().dot(D));
    double c = D.dot(D) - std::pow(radius_, 2);
    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
    }
    double t1 = -(-b + std::sqrt(discriminant)) / 2.0;
    double t2 = -(-b - std::sqrt(discriminant)) / 2.0;

    if (t1 < t2 && t1 > 0)
    {
        return true;
    }
    else if (t2 > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

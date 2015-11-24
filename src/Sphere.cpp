#include <cmath>
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

bool Sphere::doesRayIntersect(const Ray& ray, double& t) const
{
    // D is the ray from the startPoint to the center of the sphere
    Vector4D D = center_ - Vector4D(ray.startPoint());
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
        t = t1;
        return true;
    }
    else if (t2 > 0)
    {
        t = t2;
        return true;
    }
    else
    {
        return false;
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

#include <QtGlobal>
#include "IntersectionMatch.h"
#include "Ray.h"
#include "Triangle.h"

namespace
{
    const double EPSILON = 1e-5;
}

Triangle::Triangle()
{
}

Triangle::Triangle(
    const Point3D& point1,
    const Point3D& point2,
    const Point3D& point3,
    const Material& material)
: point1_(point1)
, point2_(point2)
, point3_(point3)
, material_(material)
{
    Vector3D u = point2_ - point1_;
    Vector3D v = point3_ - point1_;
    Vector3D normal = u.cross(v);
    normal.normalize();

    u_ = u;
    v_ = v;
    normal_ = normal;

    dotUU_ = u.dot(u);
    dotUV_ = u.dot(v);
    dotVV_ = v.dot(v);

    intersectTestDenominator_ = std::pow(dotUV_, 2) - dotUU_ * dotVV_;
}

Triangle::~Triangle()
{
}

IntersectionMatch Triangle::doesRayIntersect(const Ray& ray) const
{
    const double a = normal_.dot(point1_ - ray.startPoint());
    const double b = normal_.dot(ray.directionVector());

    // If Ray is parallel, (also prevents dividing by 0)
    if (std::fabs(b) < EPSILON || std::fabs(a) < EPSILON)
    {
        return IntersectionMatch();
    }
    double t = a / b;
    // Ray is going away from the plane and never intersects
    if (t < EPSILON)
    {
        return IntersectionMatch();
    }

    const Vector4D intersectionPoint = ray.pointAlongRay(t);
    const Vector4D w = intersectionPoint - Vector4D(point1_);
    const double dotWU = w.dot(u_);
    const double dotWV = w.dot(v_);

    const double s = (dotUV_ * dotWV - dotVV_ * dotWU) / intersectTestDenominator_;
    if (s < 0.0 || s > 1.0)
    {
        return IntersectionMatch();
    }
    const double q = (dotUV_ * dotWU - dotUU_ * dotWV) / intersectTestDenominator_;
    if (q < 0.0 || (q + s) > 1.0)
    {
        return IntersectionMatch();
    }

    return IntersectionMatch(true, this, t);
}

Vector4D Triangle::normal(const Vector4D& point) const
{
    // normal is the same for all points
    Q_UNUSED(point);
    return normal_;
}

const Material& Triangle::material() const
{
    return material_;
}

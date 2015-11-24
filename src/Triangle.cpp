#include <QtGlobal>
#include "Triangle.h"

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
}

Triangle::~Triangle()
{
}

bool Triangle::doesRayIntersect(const Ray& ray, double& t) const
{
    Q_UNUSED(ray);
    Q_UNUSED(t);

    // TODO
    return false;
}

Vector4D Triangle::normal(const Vector4D& point) const
{
    // normal is the same for all points
    Q_UNUSED(point);

    Vector3D u = point2_ - point1_;
    Vector3D v = point3_ - point2_;
    Vector3D normal = u.cross(v);
    normal.normalize();
    return normal;
}

const Material& Triangle::material() const
{
    return material_;
}

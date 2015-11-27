#include "Quad.h"

Quad::Quad(const Point3D& point1,
    const Point3D& point2,
    const Point3D& point3,
    const Point3D& point4,
    const Material& material)
: tri1_(point1, point2, point4, material)
, tri2_(point2, point3, point4, material)
{
    // Verify that it is on the
    if (tri1_.normal(Vector4D()) != tri2_.normal(Vector4D()))
    {
        std::cout << "All points of quad must be in the same plane." << std::endl;
        std::exit(-1);
    }
}

Quad::~Quad()
{
}

bool Quad::doesRayIntersect(const Ray& ray, double& t) const
{
    if (tri1_.doesRayIntersect(ray, t))
    {
        return true;
    }
    return tri2_.doesRayIntersect(ray, t);
}

Vector4D Quad::normal(const Vector4D& point) const
{
    return tri1_.normal(point);
}

const Material& Quad::material() const
{
    return tri1_.material();
}

#include "BoundingBoxObject.h"

BoundingBoxObject::BoundingBoxObject(const std::list<Triangle>& triangles, ModelDimensions maxDimensions)
: triangles_(triangles)
, maxDimensions_(maxDimensions)
{
    generateBox();
}

BoundingBoxObject::~BoundingBoxObject()
{
}

bool BoundingBoxObject::doesRayIntersect(const Ray& ray, double& t) const
{
    bool doesRayIntersectBox = false;
    for (const Quad& quad : boundingBox_)
    {
        if (quad.doesRayIntersect(ray, t))
        {
            doesRayIntersectBox = true;
            break;
        }
    }

    if (!doesRayIntersectBox)
    {
        return false;
    }

    bool doesRayIntersectTriangle = false;
    double nearestTvalue = std::numeric_limits<double>::max();
    for (const Triangle& tri : triangles_)
    {
        if (tri.doesRayIntersect(ray, t))
        {
            if (t < nearestTvalue)
            {
                closestTriangle_ = tri;
                nearestTvalue = t;
            }
            doesRayIntersectTriangle = true;
        }
    }

    if (doesRayIntersectTriangle)
    {

    }
    else
    {
        return false;
    }
}

Vector4D BoundingBoxObject::normal(const Vector4D& point) const
{

}

const Material& BoundingBoxObject::material() const
{

}

void BoundingBoxObject::generateBox()
{
    const Point3D point1(maxDimensions_.minX, maxDimensions_.minY, maxDimensions_.minZ);
    const Point3D point2(maxDimensions_.minX, maxDimensions_.minY, maxDimensions_.maxZ);
    const Point3D point3(maxDimensions_.minX, maxDimensions_.maxY, maxDimensions_.minZ);
    const Point3D point4(maxDimensions_.minX, maxDimensions_.maxY, maxDimensions_.maxZ);
    const Point3D point5(maxDimensions_.maxY, maxDimensions_.minY, maxDimensions_.minZ);
    const Point3D point6(maxDimensions_.maxY, maxDimensions_.minY, maxDimensions_.maxZ);
    const Point3D point7(maxDimensions_.maxY, maxDimensions_.maxY, maxDimensions_.minZ);
    const Point3D point8(maxDimensions_.maxY, maxDimensions_.maxY, maxDimensions_.maxZ);

    boundingBox_.push_back(Quad(point1, point2, point4, point3, Material()));
    boundingBox_.push_back(Quad(point2, point6, point8, point4, Material()));
    boundingBox_.push_back(Quad(point6, point5, point7, point8, Material()));
    boundingBox_.push_back(Quad(point4, point8, point7, point3, Material()));
    boundingBox_.push_back(Quad(point2, point1, point5, point6, Material()));
    boundingBox_.push_back(Quad(point5, point1, point3, point7, Material()));
}

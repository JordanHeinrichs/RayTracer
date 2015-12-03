#include <list>

#include <QtGlobal>

#include "BoundingBoxObject.h"
#include "IntersectionMatch.h"
#include "Quad.h"
#include "Ray.h"
#include "Triangle.h"

BoundingBoxObject::BoundingBoxObject(const std::list<Triangle>& triangles, ModelDimensions maxDimensions)
: triangles_(triangles)
, maxDimensions_(maxDimensions)
{
    generateBox();
}

BoundingBoxObject::~BoundingBoxObject()
{
}

IntersectionMatch BoundingBoxObject::doesRayIntersect(const Ray& ray) const
{
    bool doesRayIntersectBox = false;
    for (const Quad& quad : boundingBox_)
    {
        const auto match = quad.doesRayIntersect(ray);
        if (match)
        {
            doesRayIntersectBox = true;
            break;
        }
    }
    if (!doesRayIntersectBox)
    {
        return IntersectionMatch();
    }

    IntersectionMatch closestMatch;
    for (const Triangle& tri : triangles_)
    {
        const auto match = tri.doesRayIntersect(ray);
        if (match)
        {
            // if object is closer than current object
            if (match < closestMatch)
            {
                closestMatch = match;
            }
        }
    }

    return closestMatch;
}

Vector4D BoundingBoxObject::normal(const Vector4D& point) const
{
    Q_UNUSED(point);
    return Vector4D();
}

const Material& BoundingBoxObject::material() const
{
    // Garbage value
    return triangles_.front().material();;
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

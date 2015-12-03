#pragma once

#include <list>
#include "I_Object.h"
#include "ModelDimensions.h"
class Triangle;
class Quad;
class Material;

class BoundingBoxObject : public I_Object
{
public:
    explicit BoundingBoxObject(const std::list<Triangle>& triangles, ModelDimensions maxDimensions);
    virtual ~BoundingBoxObject();

    IntersectionMatch doesRayIntersect(const Ray& ray) const;

    Vector4D normal(const Vector4D& point) const;
    const Material& material() const;

private:
    void generateBox();

private:
    std::list<Quad> boundingBox_;
    std::list<Triangle> triangles_;
    ModelDimensions maxDimensions_;
};

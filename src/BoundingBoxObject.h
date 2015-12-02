#pragma once

#include "I_Object.h"
#include "ModelDimensions.h"

class BoundingBoxObject : public I_Object
{
public:
    explicit BoundingBoxObject(const std::list<Triangle> triangles&, ModelDimensions maxDimensions);
    virtual ~BoundingBoxObject();

    bool doesRayIntersect(const Ray& ray, double& t) const;

    Vector4D normal(const Vector4D& point) const;
    const Material& material() const;

private:
    void generateBox();

private:
    std::list<Quad> boundingBox_;
    ModelDimensions maxDimensions_;

    Triangle closestTriangle_;
    std::list<Triangle> triangles_;
};

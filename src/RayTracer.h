#pragma once

#include <memory>
class QImage;

#include "algebra.h"
class PhongCalculator;
class Ray;
class Scene;

class RayTracer
{
public:
    explicit RayTracer(const Scene& scene);
    virtual ~RayTracer();

    QImage generateImage() const;

private:
    Color trace(const Ray& ray, int depth) const;

private:
    const Scene& scene_;
    std::unique_ptr<PhongCalculator> phongCalculator_;
};
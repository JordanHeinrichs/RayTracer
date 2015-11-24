#pragma once

#include <list>
#include <memory>
#include "algebra.h"
class Ray;
class I_Object;
class Light;

class PhongCalculator
{
public:
    PhongCalculator(const std::list<Light>& lights, const std::list<std::shared_ptr<I_Object> >& objects);
    virtual ~PhongCalculator();

    Color calculate(const Point3D& point,
        const I_Object& object,
        const Point3D& viewPosition) const;

private:
    bool doesPointSeeLight(const Ray& shadowRay) const;

private:
    const std::list<Light>& lights_;
    const std::list<std::shared_ptr<I_Object> >& objects_;
};

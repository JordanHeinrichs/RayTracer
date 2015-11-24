#pragma once

#include <list>
#include <memory>
#include "algebra.h"
class I_Object;
class Light;
class Ray;

class Scene
{
public:
    Scene(int width, int height,
        const std::list<Light>& lights,
        const std::list<std::shared_ptr<I_Object> >& objects);
    virtual ~Scene();

    Ray generateCameraRay(int xPixel, int yPixel) const;
    bool doesRayIntersect(const Ray& ray, double& t, I_Object*& object) const;

    int width() const;
    int height() const;
    const std::list<Light>& lights() const;
    const std::list<std::shared_ptr<I_Object> >& objects() const;

private:
    Point3D getPointOnViewplaneFromPixel(int xPixel, int yPixel) const;

private:
    const int width_;
    const int height_;

    std::list<Light> lights_;
    std::list<std::shared_ptr<I_Object> > objects_;
};

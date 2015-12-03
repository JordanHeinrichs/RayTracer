#pragma once

#include <list>
#include <memory>
#include "algebra.h"
class I_Object;
class IntersectionMatch;
class Light;
class Ray;
class SceneSettingReader;

class Scene
{
public:
    explicit Scene(SceneSettingReader& settingsReader);
    virtual ~Scene();

    Ray generateCameraRay(int xPixel, int yPixel) const;
    IntersectionMatch doesRayIntersect(const Ray& ray) const;

    int width() const;
    int height() const;
    const std::list<Light>& lights() const;
    const std::list<std::shared_ptr<I_Object>>& objects() const;

private:
    Point3D getPointOnViewplaneFromPixel(int xPixel, int yPixel) const;

private:
    const int width_;
    const int height_;

    std::list<Light> lights_;
    std::list<std::shared_ptr<I_Object>> objects_;

    const Point3D cameraLocation_;
    const double viewportZLocation_;
    const double viewportWidth_;
    const double viewportHeight_;
};

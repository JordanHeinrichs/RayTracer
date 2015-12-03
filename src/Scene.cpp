#include "I_Object.h"
#include "IntersectionMatch.h"
#include "Light.h"
#include "Ray.h"
#include "Scene.h"
#include "SceneSettingReader.h"

Scene::Scene(SceneSettingReader& settingsReader)
: width_(settingsReader.pictureWidth())
, height_(settingsReader.pictureHeight())
, lights_(settingsReader.readLights())
, objects_(settingsReader.readObjects())
, cameraLocation_(settingsReader.cameraLocation())
, viewportZLocation_(settingsReader.viewportZLocation())
, viewportWidth_(settingsReader.viewportWidth())
, viewportHeight_(settingsReader.viewportHeight())
{
}

Scene::~Scene()
{
}

Ray Scene::generateCameraRay(int xPixel, int yPixel) const
{
    Point3D pointAlongRay = getPointOnViewplaneFromPixel(xPixel, yPixel);
    return Ray(cameraLocation_, pointAlongRay);
}

IntersectionMatch Scene::doesRayIntersect(const Ray& ray) const
{
    IntersectionMatch closestMatch;
    for (const auto& object : objects_)
    {
        auto match = object->doesRayIntersect(ray);
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

int Scene::width() const
{
    return width_;
}

int Scene::height() const
{
    return height_;
}

const std::list<Light>& Scene::lights() const
{
    return lights_;
}

const std::list<std::shared_ptr<I_Object>>& Scene::objects() const
{
    return objects_;
}

Point3D Scene::getPointOnViewplaneFromPixel(int xPixel, int yPixel) const
{
    const double x = (static_cast<double>(xPixel) / width_ - 0.5) * (viewportWidth_);
    const double y = (static_cast<double>(yPixel) / height_ - 0.5) * (viewportHeight_);
    // Flip coordinates from +y down to +y up.
    return Point3D(x, -y, viewportZLocation_);
}

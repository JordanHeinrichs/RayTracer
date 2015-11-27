#include "I_Object.h"
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

bool Scene::doesRayIntersect(const Ray& ray, double& t, I_Object*& object) const
{
    I_Object* closestObject = NULL;
    t = std::numeric_limits<double>::max();

    for(std::list<std::shared_ptr<I_Object> >::const_iterator object = objects_.begin();
        object != objects_.end(); ++object)
    {
        double objectIntersectionT;
        if ((*object)->doesRayIntersect(ray, objectIntersectionT))
        {
            // if object is closer than current object
            if (objectIntersectionT < t)
            {
                t = objectIntersectionT;
                closestObject = object->get();
            }
        }
    }

    object = closestObject;
    return object != NULL;
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

const std::list<std::shared_ptr<I_Object> >& Scene::objects() const
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

#include "I_Object.h"
#include "Light.h"
#include "Ray.h"
#include "Scene.h"

namespace
{
    const Point3D CAMERA_LOCATION = Point3D(0, 0, 0);
    const Point3D POINT_ON_VIEWPLANE = Point3D(0, 0, 5);
    const double X_VIEWPORT_SIZE = 4.0;
    const double Y_VIEWPORT_SIZE = 4.0;
}

Scene::Scene(int width, int height,
    const std::list<Light>& lights,
    const std::list<std::shared_ptr<I_Object> >& objects)
: width_(width)
, height_(height)
, lights_(lights)
, objects_(objects)
{
}

Scene::~Scene()
{
}

Ray Scene::generateCameraRay(int xPixel, int yPixel) const
{
    Point3D pointAlongRay = getPointOnViewplaneFromPixel(xPixel, yPixel);
    return Ray(CAMERA_LOCATION, pointAlongRay);
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
    const double x = (static_cast<double>(xPixel) / width_ - 0.5) * (X_VIEWPORT_SIZE);
    const double y = (static_cast<double>(yPixel) / height_ - 0.5) * (Y_VIEWPORT_SIZE);
    return Point3D(x, y, POINT_ON_VIEWPLANE[Z_INDEX]);
}

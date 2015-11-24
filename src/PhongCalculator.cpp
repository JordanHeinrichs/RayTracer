#include "I_Object.h"
#include "Light.h"
#include "Material.h"
#include "PhongCalculator.h"
#include "Ray.h"

namespace
{
    const double GLOBAL_AMBIENT_FACTOR = 0.3;
    const double EPSILON = 1e-5;
}

PhongCalculator::PhongCalculator(
    const std::list<Light>& lights,
    const std::list<std::shared_ptr<I_Object> >& objects)
: lights_(lights)
, objects_(objects)
{
}

PhongCalculator::~PhongCalculator()
{
}

Color PhongCalculator::calculate(const Point3D& point,
    const I_Object& object,
    const Point3D& viewPosition) const
{
    const Vector4D normal = object.normal(point);

    Color color = object.material().ambient() * GLOBAL_AMBIENT_FACTOR;
    for(std::list<Light>::const_iterator light = lights_.begin(); light != lights_.end(); ++light)
    {
        Ray shadowRay(point, light->position());
        if (doesPointSeeLight(shadowRay))
        {
            color += object.material().diffuse() * std::max(shadowRay.directionVector().dot(normal), 0.0)
                * light->diffuse();
            Vector4D reflection = (2 * shadowRay.directionVector().dot(normal) * normal)
                - shadowRay.directionVector();
            Vector4D v = viewPosition - point;
            reflection.normalize();
            v.normalize();
            color += object.material().specular() * light->specular()
                * std::pow(std::max(reflection.dot(v), 0.0), object.material().shininess());
        }
    }
    return color;
}

bool PhongCalculator::doesPointSeeLight(const Ray& shadowRay) const
{
    for(std::list<std::shared_ptr<I_Object> >::const_iterator object = objects_.begin();
        object != objects_.end(); ++object)
    {
        double t = 0.0;
        if (!(*object)->doesRayIntersect(shadowRay, t) || t < EPSILON)
        {
            return true;
        }
    }
    return false;
}

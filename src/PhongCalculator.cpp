#include "I_Object.h"
#include "IntersectionMatch.h"
#include "Light.h"
#include "Material.h"
#include "PhongCalculator.h"
#include "Ray.h"

namespace
{
    const double GLOBAL_AMBIENT_FACTOR = 0.1;
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
    Vector4D viewVector = viewPosition - point;
    viewVector.normalize();
    Vector4D normal = object.normal(point);
    flipNormalIfNeeded(normal, viewVector);

    Color color = object.material().ambient() * GLOBAL_AMBIENT_FACTOR;
    for(const auto& light : lights_)
    {
        Ray shadowRay(point, light.position());
        if (doesPointSeeLight(shadowRay))
        {
            color += object.material().diffuse() * std::max(shadowRay.directionVector().dot(normal), 0.0)
                * light.diffuse();
            Vector4D reflection = (2 * shadowRay.directionVector().dot(normal) * normal)
                - shadowRay.directionVector();
            reflection.normalize();
            color += object.material().specular() * light.specular()
                * std::pow(std::max(reflection.dot(viewVector), 0.0), object.material().shininess());
        }
    }
    return color;
}

bool PhongCalculator::doesPointSeeLight(const Ray& shadowRay) const
{
    for(const auto& object : objects_)
    {
        auto match = object->doesRayIntersect(shadowRay);
        if (!match || match.t() < EPSILON)
        {
            return true;
        }
    }
    return false;
}

void PhongCalculator::flipNormalIfNeeded(Vector4D& normal, const Vector4D& viewVector) const
{
    if (normal.dot(viewVector) < 0.0)
    {
        normal = -normal;
    }
}

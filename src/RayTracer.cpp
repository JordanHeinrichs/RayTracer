#include <QImage>
#include <QColor>

#include "PhongCalculator.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Scene.h"

namespace
{
    const Color BACKGROUND_COLOR = Color(0.2, 0.2, 0.2);
    const int MAX_DEPTH = 1;
}

RayTracer::RayTracer(const Scene& scene)
: scene_(scene)
, phongCalculator_(new PhongCalculator(scene.lights(), scene.objects()))
{
}

RayTracer::~RayTracer()
{
}

QImage RayTracer::generateImage() const
{
    QImage image(scene_.width(), scene_.height(), QImage::Format_RGB32);

    // iterate over the pixels & set color values
    for (int x = 0; x < scene_.width(); ++x)
    {
        for (int y = 0; y < scene_.height(); ++y)
        {
            Ray ray = scene_.generateCameraRay(x, y);
            Color color = trace(ray, 1);
            image.setPixel(x, y,
                qRgb(color.red() * 255, color.green() * 255, color.blue() * 255));
        }
    }
    return image;
}

Color RayTracer::trace(const Ray& ray, int depth) const
{
    if (depth > MAX_DEPTH)
    {
        return BACKGROUND_COLOR;
    }

    I_Object* object = NULL;
    double t = 0.0;
    if (!scene_.doesRayIntersect(ray, t, object))
    {
        return BACKGROUND_COLOR;
    }

    Color localColor =  phongCalculator_->calculate(ray.pointAlongRay(t), *object, ray.startPoint());
    return localColor;
}

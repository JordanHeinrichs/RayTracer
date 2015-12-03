#include <thread>
#include <ctime>

#include <QImage>
#include <QColor>

#include "I_Object.h"
#include "IntersectionMatch.h"
#include "PhongCalculator.h"
#include "Ray.h"
#include "RayTracer.h"
#include "Scene.h"

namespace
{
    const Color BACKGROUND_COLOR = Color(0.2, 0.2, 0.2);
    const int MAX_DEPTH = 3;
    const int NUMBER_OF_THREADS = 4;
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
    QRgb* imageData = reinterpret_cast<QRgb*>(image.bits());

    int sectionHeight = scene_.height() / NUMBER_OF_THREADS;

    std::vector<std::thread> threads;
    time_t start;
    time(&start);

    for (int i = 0; i < NUMBER_OF_THREADS - 1; ++i)
    {
        const int yLower = i * sectionHeight;
        const int yUpper = (i + 1) * sectionHeight;
        threads.push_back(std::thread(&RayTracer::rayTraceSection, this, yLower, yUpper, imageData));
    }

    rayTraceSection(sectionHeight * (NUMBER_OF_THREADS - 1), scene_.height(), imageData);

    for(auto &t : threads)
    {
        t.join();
    }
    time_t end;
    time(&end);
    std::cout << "Frame rendering took " << difftime(end, start) << " seconds" << std::endl;
    return image;
}

void RayTracer::rayTraceSection(int yLower, int yUpper, QRgb* imageData) const
{
    for (int y = yLower; y < yUpper; ++y)
    {
        for (int x = 0; x < scene_.width(); ++x)
        {
            auto ray = scene_.generateCameraRay(x, y);
            auto color = trace(ray, 1);
            imageData[(y * scene_.width()) + x] = qRgb(color.red() * 255, color.green() * 255, color.blue() * 255);
        }
    }
}

Color RayTracer::trace(const Ray& ray, int depth) const
{
    if (depth > MAX_DEPTH)
    {
        return BACKGROUND_COLOR;
    }

    auto match = scene_.doesRayIntersect(ray);
    if (!match)
    {
        return BACKGROUND_COLOR;
    }

    const Point3D intersectPoint = ray.pointAlongRay(match.t());
    Color localColor =  phongCalculator_->calculate(intersectPoint, *match.object(), ray.startPoint());
    Color reflectedColor = trace(reflectionRay(ray, *match.object(), intersectPoint), depth + 1);
    return localColor + reflectedColor;
}

Ray RayTracer::reflectionRay(const Ray& ray, const I_Object& object, const Point3D& point) const
{
    const Vector4D normal = object.normal(point);
    Vector4D reflection = ray.directionVector() - (2 * ray.directionVector().dot(normal) * normal);
    reflection.normalize();
    return Ray(point, reflection);
}

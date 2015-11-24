#include <memory>
#include <QImage>
#include <QColor>
#include "algebra.h"
#include "Light.h"
#include "RayTracer.h"
#include "Scene.h"
#include "Sphere.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    // TODO: prompt user on command line for dimensions
    int width = 1000;
    int height = 1000;

    Material sphere1Material(Color(1, 1, 1), Color(1, 0, 0), Color(1, 0, 0), 10.0);
    std::shared_ptr<I_Object> sphere1(new Sphere(Point3D(2, 0, 10), 1, sphere1Material));

    Material sphere2Material(Color(1, 1, 1), Color(0, 1, 0), Color(0, 1, 0.3), 10.0);
    std::shared_ptr<I_Object> sphere2(new Sphere(Point3D(-0.8, 2, 11), 1.3, sphere2Material));

    Material sphere3Material(Color(1, 1, 1), Color(0, 0, 1), Color(0.2, 0, 1), 5.0);
    std::shared_ptr<I_Object> sphere3(new Sphere(Point3D(-1.7, -2.2, 8), 1.1, sphere3Material));

    std::list<std::shared_ptr<I_Object> > objects;
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);

    Light light1(Point3D(5, 5, 0), Color(1, 1, 1), Color(1, 1, 1));
    Light light2(Point3D(-5, -7, 3), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5));
    std::list<Light> lights = {light1, light2};

    Scene scene(width, height, lights, objects);
    RayTracer rayTracer(scene);

    QImage image = rayTracer.generateImage();
    // TODO: prompt user on command line for output name
    image.save("output.png");

    return 0;
}

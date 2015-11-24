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
    int width = 100;
    int height = 100;

    std::shared_ptr<I_Object> sphere1(new Sphere(Point3D(0, 0, 10), 3, Material(Color(1, 0, 0), 0.3)));
    std::list<std::shared_ptr<I_Object> > objects;
    objects.push_back(sphere1);

    Light light(Point3D(0, 0, 0), Color(1, 1, 1), Color(1, 1, 1));
    std::list<Light> lights = {light};

    Scene scene(width, height, lights, objects);
    RayTracer rayTracer(scene);

    QImage image = rayTracer.generateImage();
    // TODO: prompt user on command line for output name
    image.save("output.png");

    return 0;
}

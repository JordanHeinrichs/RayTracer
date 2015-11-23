#include <QImage>
#include <QColor>
#include "algebra.h"
#include <Ray.h>
#include <Sphere.h>

namespace
{
    const Point3D CAMERA_LOCATION = Point3D(0, 0, 0);
    const Point3D POINT_ON_VIEWPLANE = Point3D(0, 0, 5);
    const double X_VIEWPORT_SIZE = 4.0;
    const double Y_VIEWPORT_SIZE = 4.0;
    const Point3D LOWER_VIEWPORT_POINT = Point3D(-2, -2, POINT_ON_VIEWPLANE[Z_INDEX]);
    const Point3D UPPER_VIEWPORT_POINT = Point3D(2, 2, POINT_ON_VIEWPLANE[Z_INDEX]);
}

Point3D getPointOnViewplaneFromPixel(int x, int y, int width, int height);

int main(int argc, char *argv[])
{
    // currently unused parameters
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    // image width and height
    // TODO: prompt user on command line for dimensions
    int width = 500;
    int height = 500;

    Sphere sphere(Point3D(0, 0, 10), 3);

    // create new image
    QImage image(width, height, QImage::Format_RGB32);

    // iterate over the pixels & set colour values
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Point3D pointAlongLine = getPointOnViewplaneFromPixel(x, y, width, height);
            Ray ray(CAMERA_LOCATION, pointAlongLine);

            double r = 0.0;
            double g = 0.0;
            double b = 0.0;
            bool intersected = sphere.doesRayIntersects(ray);
            if (intersected)
            {
                r = 1.0;
            }
            image.setPixel(x, y,
                qRgb(r * 255, g * 255, b * 255));
        }
    }

    // save to file
    // TODO: prompt user on command line for output name
    image.save("output.png");

    // application successfully returned
    return 0;
}

Point3D getPointOnViewplaneFromPixel(int x, int y, int width, int height)
{
    const double xCoordinate = (static_cast<double>(x) / width - 0.5) * (X_VIEWPORT_SIZE);
    const double yCoordinate = (static_cast<double>(y) / height - 0.5) * (Y_VIEWPORT_SIZE);
    return Point3D(xCoordinate, yCoordinate, POINT_ON_VIEWPLANE[Z_INDEX]);
}

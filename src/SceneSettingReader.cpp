#include <QString>
#include "Material.h"
#include "Quad.h"
#include "SceneSettingReader.h"
#include "Sphere.h"
#include "Triangle.h"

namespace
{
    const QString DIMENSION_GROUP = "Dimensions";
    const QString VIEWPORT_GROUP = "Viewport";
    const QString CAMERA_LOCATION_GROUP = "CameraLocation";
    const QString OBJECTS_GROUP = "Objects";
    const QString LIGHTS_GROUP = "Lights";
}

SceneSettingReader::SceneSettingReader(const QString& settingsFilename)
: settings_(settingsFilename, QSettings::IniFormat)
{
}

SceneSettingReader::~SceneSettingReader()
{
}

QString SceneSettingReader::outputFilename() const
{
    return settings_.value("Output/filename", QString("output.png")).toString();
}

int SceneSettingReader::pictureWidth()
{
    return settings_.value(DIMENSION_GROUP + "/width", 3840).toInt();
}

int SceneSettingReader::pictureHeight()
{
    return settings_.value(DIMENSION_GROUP + "/height", 2160).toInt();
}

double SceneSettingReader::viewportWidth()
{
    return settings_.value(VIEWPORT_GROUP + "/width", 4.0).toDouble();
}

double SceneSettingReader::viewportHeight()
{
    return settings_.value(VIEWPORT_GROUP + "/height", 3.0).toDouble();
}

double SceneSettingReader::viewportZLocation()
{
    return settings_.value(VIEWPORT_GROUP + "/zDistance", 5.0).toDouble();
}

Point3D SceneSettingReader::cameraLocation()
{
    settings_.beginGroup(CAMERA_LOCATION_GROUP);
    const auto cameraLocation = readPoint();
    settings_.endGroup();
    return cameraLocation;
}

std::list<std::shared_ptr<I_Object> > SceneSettingReader::readObjects()
{
    std::list<std::shared_ptr<I_Object> > objects;
    settings_.beginGroup(OBJECTS_GROUP);
    const int size = settings_.beginReadArray("objects");
    for (int i = 0; i < size; ++i)
    {
        settings_.setArrayIndex(i);
        if (settings_.value("type").toString() == "sphere")
        {
            objects.push_back(std::shared_ptr<I_Object>(readSphere()));
        }
        else if (settings_.value("type").toString() == "triangle")
        {
            objects.push_back(std::shared_ptr<I_Object>(readTriangle()));
        }
        else if (settings_.value("type").toString() == "quad")
        {
            objects.push_back(std::shared_ptr<I_Object>(readQuad()));
        }
        else
        {
            std::cout << "Error: object type is not valid"
                << settings_.value("type").toString().toStdString() << std::endl;
        }
    }
    settings_.endArray();
    settings_.endGroup();
    return objects;
}

std::list<Light> SceneSettingReader::readLights()
{
    std::list<Light> lights;
    settings_.beginGroup(LIGHTS_GROUP);
    const int size = settings_.beginReadArray("lights");
    for (int i = 0; i < size; ++i)
    {
        settings_.setArrayIndex(i);
        settings_.beginGroup("diffuse");
        const Color diffuse = readColor();
        settings_.endGroup();
        settings_.beginGroup("specular");
        const Color specular = readColor();
        settings_.endGroup();
        lights.push_back(Light(readPoint(), diffuse, specular));
    }
    settings_.endArray();
    settings_.endGroup();
    return lights;
}

Point3D SceneSettingReader::readPoint() const
{
    return Point3D(settings_.value("x").toDouble(),
        settings_.value("y").toDouble(),
        settings_.value("z").toDouble());
}

Color SceneSettingReader::readColor() const
{
    return Color(settings_.value("red").toDouble(),
        settings_.value("green").toDouble(),
        settings_.value("blue").toDouble());
}

I_Object* SceneSettingReader::readSphere()
{
    settings_.beginGroup("center");
    const auto center = readPoint();
    settings_.endGroup();
    const double radius = settings_.value("radius").toDouble();
    return new Sphere(center, radius, readMaterial());
}

I_Object* SceneSettingReader::readTriangle()
{
    settings_.beginGroup("point1");
    const auto point1 = readPoint();
    settings_.endGroup();
    settings_.beginGroup("point2");
    const auto point2 = readPoint();
    settings_.endGroup();
    settings_.beginGroup("point3");
    const auto point3 = readPoint();
    settings_.endGroup();

    return new Triangle(point1, point2, point3, readMaterial());
}

I_Object* SceneSettingReader::readQuad()
{
    settings_.beginGroup("point1");
    const auto point1 = readPoint();
    settings_.endGroup();
    settings_.beginGroup("point2");
    const auto point2 = readPoint();
    settings_.endGroup();
    settings_.beginGroup("point3");
    const auto point3 = readPoint();
    settings_.endGroup();
    settings_.beginGroup("point4");
    const auto point4 = readPoint();
    settings_.endGroup();

    return new Quad(point1, point2, point3, point4, readMaterial());
}

Material SceneSettingReader::readMaterial()
{
    settings_.beginGroup("material");
    settings_.beginGroup("diffuse");
    const Color diffuse = readColor();
    settings_.endGroup();
    settings_.beginGroup("specular");
    const Color specular = readColor();
    settings_.endGroup();
    settings_.beginGroup("ambient");
    const Color ambient = readColor();
    settings_.endGroup();
    const double shininess = settings_.value("shininess").toDouble();
    settings_.endGroup();
    return Material(specular, diffuse, ambient, shininess);
}

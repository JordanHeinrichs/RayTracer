#pragma once

#include <list>
#include <memory>

#include <QSettings>
class QString;

#include "algebra.h"
#include "I_Object.h"
#include "Light.h"
class Material;

class SceneSettingReader
{
public:
    explicit SceneSettingReader(const QString& settingsFilename);
    virtual ~SceneSettingReader();

    QString outputFilename() const;

    int pictureWidth();
    int pictureHeight();

    double viewportWidth();
    double viewportHeight();
    double viewportZLocation();

    Point3D cameraLocation();

    std::list<std::shared_ptr<I_Object> > readObjects();
    std::list<Light> readLights();

private:
    Point3D readPoint() const;
    Color readColor() const;

    I_Object* readSphere();
    I_Object* readTriangle();
    I_Object* readQuad();
    Material readMaterial();

private:
    QSettings settings_;
};

#include <memory>
#include <QImage>
#include <QColor>
#include "algebra.h"
#include "RayTracer.h"
#include "Scene.h"
#include "SceneSettingReader.h"

namespace
{
    const QString SETTINGS_FILENAME = "sceneSpecificationRc";
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    SceneSettingReader settingsReader(SETTINGS_FILENAME);
    Scene scene(settingsReader);
    RayTracer rayTracer(scene);

    QImage image = rayTracer.generateImage();
    image.save(settingsReader.outputFilename());

    return 0;
}

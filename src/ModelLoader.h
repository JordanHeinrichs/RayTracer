#pragma once

#include <list>
#include <vector>

#include "ModelDimensions.h"
#include "ObjTriangle.h"
#include "Triangle.h"

class ModelLoader
{
public:
    ModelLoader(const QString& filename,
        const Point3D& center,
        double maxDimension,
        double xRotationDegree,
        double yRotationDegree,
        double zRotationDegree,
        const Material& material);
    virtual ~ModelLoader();

    std::list<Triangle> triangles() const;
    ModelDimensions maxDimensions() const;

private:
    void scaleAndCenterModel(float maxDimension);

    bool loadModel(const QString& filename);

    bool parseLine(const QString& line);
    bool parseVertexLine(const QString& line);
    bool parseTextureCoordinateLine(const QString& line);
    bool parseFaceElementLine(const QString& line);

    ModelDimensions findMaxDimensions() const;

private:
    const Point3D center_;
    double xRotationDegree_;
    double yRotationDegree_;
    double zRotationDegree_;
    ModelDimensions maxDimensions_;

    const Material material_;

    std::vector<Point3D> indexedVertices_;
    std::vector<Point2D> indexedTextureCoordinates_;
    std::vector<ObjTriangle> objTriangles_;
};

#pragma once

#include <list>
#include <vector>

#include "I_Object.h"
#include "Triangle.h"
#include "ObjTriangle.h"

class ModelLoader
{
public:
    ModelLoader(const QString& filename, const Point3D& center, double maxDimension, const Material& material);
    virtual ~ModelLoader();

    std::list<Triangle> triangles() const;

private:
    void scaleAndCenterModel(float maxDimension);

    bool loadModel(const QString& filename);

    bool parseLine(const QString& line);
    bool parseVertexLine(const QString& line);
    bool parseTextureCoordinateLine(const QString& line);
    bool parseFaceElementLine(const QString& line);

private:
    const Point3D center_;
    const Material material_;

    std::vector<Point3D> indexedVertices_;
    std::vector<Point2D> indexedTextureCoordinates_;
    std::vector<ObjTriangle> objTriangles_;
};

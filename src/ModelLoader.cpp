#define _USE_MATH_DEFINES
#include <cmath>

#include <QColor>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include "ModelLoader.h"

namespace
{
    const QRegularExpression VERTEX_ROW("(-?\\d+\\.\\d+) (-?\\d+\\.\\d+) (-?\\d+\\.\\d+)$");
    const QRegularExpression TEXTURE_COORDINATE_ROW("(-?\\d+\\.\\d+) (-?\\d+\\.\\d+)$");
    const QRegularExpression FACE_ELEMENT_ROW("(\\d+)/(\\d+) (\\d+)/(\\d+) (\\d+)/(\\d+)$");

    const int FLOATS_PER_TRIANGLE = 9; // 3 vertices per triangle * 3 floats per vertex
    const float NORMAL_LINE_LENGTH = 0.3f;

    const QColor FACE_LINE_COLOR = Qt::blue;
    const QColor VERTEX_LINE_COLOR = Qt::red;

    double degToRad(double degree)
    {
        return degree * M_PI / 180;
    }
}

ModelLoader::ModelLoader(const QString& filename,
    const Point3D& center,
    double maxDimension,
    double xRotationDegree,
    double yRotationDegree,
    double zRotationDegree,
    const Material& material)
: center_(center)
, xRotationDegree_(xRotationDegree)
, yRotationDegree_(yRotationDegree)
, zRotationDegree_(zRotationDegree)
, material_(material)
{
    if (!loadModel(filename))
    {
        std::cout << "Unable to load model: " << qPrintable(filename) << std::endl;
        std::exit(-1);
    }
    scaleAndCenterModel(maxDimension);
}

ModelLoader::~ModelLoader()
{
}

std::list<Triangle> ModelLoader::triangles() const
{
    std::list<Triangle> triangles_;
    for (auto tri : objTriangles_)
    {
        triangles_.push_back(Triangle(indexedVertices_[tri.indexOfVertices[0]],
            indexedVertices_[tri.indexOfVertices[1]],
            indexedVertices_[tri.indexOfVertices[2]],
            material_));
    }
    return triangles_;
}

ModelDimensions ModelLoader::maxDimensions() const
{
    return maxDimensions_;
}

void ModelLoader::scaleAndCenterModel(float maxDimension)
{

    ModelDimensions dimensions = findMaxDimensions();
    const float xDifference = dimensions.maxX - dimensions.minX;
    const float yDifference = dimensions.maxY - dimensions.minY;
    const float zDifference = dimensions.maxZ - dimensions.minZ;
    float scalingFactor = 1;
    if (xDifference > yDifference && xDifference > zDifference)
    {
        scalingFactor = maxDimension / xDifference;
    }
    else if (yDifference > zDifference)
    {
        scalingFactor = maxDimension / yDifference;
    }
    else
    {
        scalingFactor = maxDimension / zDifference;
    }

    const float xShift = (dimensions.maxX + dimensions.minX) / 2.0;
    const float yShift = (dimensions.maxY + dimensions.minY) / 2.0;
    const float zShift = (dimensions.maxZ + dimensions.minZ) / 2.0;

    Matrix4x4 xRotation = Matrix4x4(
        Vector4D(1, 0, 0, 0),
        Vector4D(0, cos(degToRad(xRotationDegree_)), -sin(degToRad(xRotationDegree_)), 0),
        Vector4D(0, sin(degToRad(xRotationDegree_)), cos(degToRad(xRotationDegree_)), 0),
        Vector4D(0, 0, 0, 1));

    Matrix4x4 yRotation = Matrix4x4(
        Vector4D(cos(degToRad(yRotationDegree_)), 0, sin(degToRad(yRotationDegree_)), 0),
        Vector4D(0, 1, 0, 0),
        Vector4D(-sin(degToRad(yRotationDegree_)), 0, cos(degToRad(yRotationDegree_)), 0),
        Vector4D(0, 0, 0, 1));

    Matrix4x4 zRotation = Matrix4x4(
        Vector4D(cos(degToRad(zRotationDegree_)), -sin(degToRad(zRotationDegree_)), 0, 0),
        Vector4D(-sin(degToRad(zRotationDegree_)), cos(degToRad(zRotationDegree_)), 0, 0),
        Vector4D(0, 0, 1, 0),
        Vector4D(0, 0, 0, 1));

    Matrix4x4 rotationTransform = zRotation * yRotation * xRotation;

    for (std::vector<Point3D>::iterator vertex = indexedVertices_.begin(); vertex != indexedVertices_.end(); ++vertex)
    {
        Vector4D VertexAroundOrigin((*vertex) - Point3D(xShift, yShift, zShift));
        (*vertex) = (scalingFactor * (rotationTransform * VertexAroundOrigin)).toPoint() + center_;
    }

    maxDimensions_ = findMaxDimensions();
}

bool ModelLoader::loadModel(const QString& filename)
{
    QFile objFile(filename);
    if (!objFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Unable to open file" << std::endl;
        return false;
    }
    QTextStream data(&objFile);

    while (!data.atEnd())
    {
        QString line = data.readLine();
        bool successful = parseLine(line);
        if (!successful)
        {
            return false;
        }
    }
    return true;
}

bool ModelLoader::parseLine(const QString& line)
{
    if (line.startsWith("v "))
    {
        return parseVertexLine(line);
    }
    else if (line.startsWith("vt "))
    {
        return parseTextureCoordinateLine(line);
    }
    else if (line.startsWith("f "))
    {
        return parseFaceElementLine(line);
    }
    return true;
}

bool ModelLoader::parseVertexLine(const QString& line)
{
    QRegularExpressionMatch match = VERTEX_ROW.match(line);
    if (match.hasMatch())
    {
        indexedVertices_.push_back(Point3D(match.captured(1).toFloat(),
            match.captured(2).toFloat(), match.captured(3).toFloat()));
        return true;
    }
    else
    {
        std::cout << "Failed to parse vertex line" << std::endl;
        return false;
    }
}

bool ModelLoader::parseTextureCoordinateLine(const QString& line)
{
    QRegularExpressionMatch match = TEXTURE_COORDINATE_ROW.match(line);
    if (match.hasMatch())
    {
        indexedTextureCoordinates_.push_back(Point2D(match.captured(1).toFloat(), match.captured(2).toFloat()));
        return true;
    }
    else
    {
        std::cout << "Failed to parse texture coordinate line" << std::endl;
        return false;
    }
}

bool ModelLoader::parseFaceElementLine(const QString& line)
{
    QRegularExpressionMatch match = FACE_ELEMENT_ROW.match(line);
    if (match.hasMatch())
    {
        ObjTriangle triangle;
        triangle.indexOfVertices[0] = match.captured(1).toInt() - 1;
        triangle.indexOfVertices[1] = match.captured(3).toInt() - 1;
        triangle.indexOfVertices[2] = match.captured(5).toInt() - 1;

        triangle.indexOfTextureCoordinates[0] = match.captured(2).toInt() - 1;
        triangle.indexOfTextureCoordinates[1] = match.captured(4).toInt() - 1;
        triangle.indexOfTextureCoordinates[2] = match.captured(6).toInt() - 1;

        objTriangles_.push_back(triangle);
        return true;
    }
    else
    {
        std::cout << "Failed to parse face element line" << std::endl;
        return false;
    }
}

ModelDimensions ModelLoader::findMaxDimensions() const
{
    ModelDimensions dimensions;
    dimensions.minX = 1e10;
    dimensions.maxX = -1e10;
    dimensions.minY = 1e10;
    dimensions.maxY = -1e10;
    dimensions.minZ = 1e10;
    dimensions.maxZ = -1e10;

    for(const auto vertex : indexedVertices_)
    {
        dimensions.minX = std::min(dimensions.minX, vertex[X_INDEX]);
        dimensions.maxX = std::max(dimensions.maxX, vertex[X_INDEX]);
        dimensions.minY = std::min(dimensions.minY, vertex[Y_INDEX]);
        dimensions.maxY = std::max(dimensions.maxY, vertex[Y_INDEX]);
        dimensions.minZ = std::min(dimensions.minZ, vertex[Z_INDEX]);
        dimensions.maxZ = std::max(dimensions.maxZ, vertex[Z_INDEX]);
    }
    return dimensions;
}

#pragma once

class ObjTriangle
{
public:
    ObjTriangle();
    virtual ~ObjTriangle();

    int indexOfVertices[3];
    int indexOfTextureCoordinates[3];
};

#pragma once

class I_Object
{
public:
    virtual ~I_Object() {}

    virtual bool doesRayIntersects(const Ray& ray) const = 0;
};

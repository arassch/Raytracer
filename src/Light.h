#ifndef LIGHT_H
#define LIGHT_H
#include <vector>
#include <Vector3.h>
#include "Object.h"

using namespace LA;

class Light
{
    Material m_material;

public:
    Light(Material mat);
    virtual ~Light();

    Vector3 getDiffuse() const  {    return m_material.diffuse;    }
    Vector3 getSpecular() const {    return m_material.specular;   }

    virtual std::vector<Vector3> getSamples() = 0;

    virtual bool isPoint() = 0;

    virtual bool intersects(Ray& ray, Scalar& t) = 0;

    virtual Object* getObject() = 0;

    Material getMaterial() { return m_material; }

};

class PointLight : public Light
{
    Vector3 m_position;

public:
    PointLight(Vector3 position, Material mat);

    vector<Vector3> getSamples();

    bool isPoint() { return true; }

    bool intersects(Ray& ray, Scalar& t) { return false; }

    Object* getObject() { return 0; }
};

class SquareLight : public Light
{
    Square m_square;
    int m_resx, m_resy;

public:
    SquareLight(Square square, int resx, int resy,
                Material mat);

    vector<Vector3> getSamples();

    bool isPoint() { return false; }

    bool intersects(Ray& ray, Scalar& t);

    Object* getObject() { return &m_square; }
};
#endif // LIGHT_H

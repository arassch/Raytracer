#ifndef OBJECT_H
#define OBJECT_H

#include "Definitions.h"
#include <TriMesh.h>
#include <BinaryAABBTree.h>

struct Material
{
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    Scalar shininess;
};

class Object
{
protected:
    Material m_material;

public:
    string m_name;

    Object(string name, Material& material) :
            m_name(name), m_material(material) {}
    virtual ~Object() {}

    virtual bool intersects(Ray& ray, Scalar& t, Vector3& normal) = 0;

    Material getMaterial() { return m_material; }
};

class Sphere : public Object
{
    Vector3 m_center;
    Scalar m_radius;

public:
    Sphere(string name, Material& material, Vector3 center, Scalar radius);
    virtual ~Sphere() {}

    bool intersects(Ray& ray, Scalar& t, Vector3& normal);
};

class Plane : public Object
{
    Vector3 m_position;
    Vector3 m_normal;

public:
    Plane(string name, Material& material, Vector3 position, Vector3 normal);
    virtual ~Plane() {}

    bool intersects(Ray& ray, Scalar& t, Vector3& normal);
};

class Square : public Object
{
    Vector3 m_corner1;
    Vector3 m_corner2;
    Vector3 m_corner3;
    Vector3 m_normal;

public:
    Square(string name, Material& material, Vector3 corner1, Vector3 corner2, Vector3 corner3, Vector3 normal);
    virtual ~Square() {}

    bool intersects(Ray& ray, Scalar& t, Vector3& normal);

    Vector3 getCorner1() const { return m_corner1; }
    Vector3 getCorner2() const { return m_corner2; }
    Vector3 getCorner3() const { return m_corner3; }
};

class Mesh : public Object
{
    string m_filename;
    TriMesh* m_mesh;
    BinaryAABBTree* m_aabbTree;

public:
    Mesh(string name, Material& material, string filename, Scalar scale = 1.0);
    virtual ~Mesh();

    bool intersects(Ray& ray, Scalar& t, Vector3& normal);
};

#endif // OBJECT_H

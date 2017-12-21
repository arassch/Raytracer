#include "Object.h"


Sphere::Sphere(string name, Material& material, Vector3 center, Scalar radius) :
    Object(name, material), m_center(center), m_radius(radius) {}

bool Sphere::intersects(Ray& ray, Scalar& t, Vector3& normal)
{
    Scalar a = Vector3::dotProd(ray.direction, ray.direction);
    Scalar b = Vector3::dotProd(ray.direction*2, ray.origin - m_center);
    Scalar c = Vector3::dotProd(ray.origin - m_center, ray.origin - m_center) - m_radius*m_radius;

    Scalar insideRoot = b*b - 4*a*c;
    Scalar t0, t1;
    if(insideRoot < 0)
        return false;
    else if(insideRoot == 0)
        t = -b / (2.0f * a);
    else //If discriminant is positive one or two intersections (two solutions) exists
    {
        Scalar sqrt_disc = sqrt(insideRoot);
        t0 = (-b - sqrt_disc) / (2.0f * a);
        t1 = (-b + sqrt_disc) / (2.0f * a);
        t = t0;
        if(t0 < 0 && t1 < 0)
            return false;
        if(t0 < 0 && t1 >= 0)
            t = t1;
        else if(t0 >= 0 && t1 < 0)
            t = t0;
        else
            t = std::min(t0,t1);
    }

    Vector3 position = ray.origin + ray.direction*t;
    normal = position - m_center;
    normal.normalize();
    return true;
}

Plane::Plane(string name, Material& material, Vector3 position, Vector3 normal) :
    Object(name, material), m_position(position), m_normal(normal) {}

bool Plane::intersects(Ray& ray, Scalar& t, Vector3& normal)
{
    Scalar denom = Vector3::dotProd(m_normal, ray.direction);
    if (abs(denom) > 0.0001f) // your favorite epsilon
    {
        t = Vector3::dotProd(m_position - ray.origin, m_normal) / denom;
        if (t >= 0)
        {
            normal = m_normal;
            return true; // you might want to allow an epsilon here too
        }
    }
    return false;
}

Square::Square(string name, Material &material,
               Vector3 corner1, Vector3 corner2, Vector3 corner3,
               Vector3 normal) :
    Object(name, material),
    m_corner1(corner1), m_corner2(corner2), m_corner3(corner3),
    m_normal(normal)
{

}

bool Square::intersects(Ray &ray, Scalar &t, Vector3 &normal)
{
    Vector3 end = ray.origin + 99999*ray.direction;
    Vector3 bary2, point;
    Vector2 bary1;
    bool ninv;
    if(CDQueries::EdgeFaceQueryDiscrete(ray.origin, end,
                                     m_corner1, m_corner2, m_corner3,
                                     bary1, bary2, point, normal, ninv))
    {
        normal = m_normal;
        t = bary1[1]*99999;
        return true;
    }

    Vector3 corner4 = m_corner1 + (((m_corner2 + m_corner3) * 0.5) - m_corner1)*2;
    if(CDQueries::EdgeFaceQueryDiscrete(ray.origin, end,
                                     m_corner2, m_corner3, corner4,
                                     bary1, bary2, point, normal, ninv))
    {
        normal = m_normal;
        t = bary1[1]*99999;
        return true;
    }

    return false;
}

Mesh::Mesh(string name, Material& material, string filename, Scalar scale) :
    Object(name, material), m_filename(filename)
{
    m_mesh = TriMesh::ReadFromFile(filename.c_str(), TriMesh::OBJ, scale);
    m_mesh->ComputeNormals();
    m_aabbTree = new BinaryAABBTree(m_mesh);
}

Mesh::~Mesh()
{
//    if(m_aabbTree)
//        delete(m_aabbTree);
//    m_aabbTree = 0;

    if(m_mesh)
        delete(m_mesh);
    m_mesh = 0;
}

bool Mesh::intersects(Ray& ray, Scalar& t, Vector3& normal)
{
    Vector3 point, bary;
    int faceId;
    if (m_aabbTree->getClosestRayIntersection(ray.origin, ray.direction, t, point, normal, faceId, bary))
    {
        TriFace* face = m_mesh->Faces()[faceId];
        normal = face->Vertex1()->Normal()*bary[0] +
                 face->Vertex2()->Normal()*bary[1] +
                 face->Vertex3()->Normal()*bary[2];
        normal.normalize();
        return true;
    }
    return false;
}





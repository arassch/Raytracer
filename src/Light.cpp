#include "Light.h"

Light::Light(Material mat) :
    m_material(mat) {}

Light::~Light() {}



PointLight::PointLight(Vector3 position, Material mat) :
    Light(mat), m_position(position)
{

}

vector<Vector3> PointLight::getSamples()
{
    vector<Vector3> samples;
    samples.push_back(m_position);
    return samples;
}

SquareLight::SquareLight(Square square, int resx, int resy, Material mat) :
Light(mat), m_square(square), m_resx(resx), m_resy(resy)
{

}

vector<Vector3> SquareLight::getSamples()
{
    vector<Vector3> samples;
    Vector3 corner = m_square.getCorner1();
    Vector3 dirx = m_square.getCorner2() - corner;
    Vector3 diry = m_square.getCorner3() - corner;

    dirx *= 1.0/m_resx;
    diry *= 1.0/m_resy;
    for(int i=0; i<=m_resx; ++i)
    {
        for(int j=0; j<=m_resy; ++j)
        {
            samples.push_back(corner + dirx*i + diry*j);
        }
    }
    return samples;
}

bool SquareLight::intersects(Ray &ray, Scalar &t)
{
    Vector3 n;
    return m_square.intersects(ray, t, n);
}

#include "RenderAlg.h"
#include "Scene.h"









RenderAlg::RenderAlg(Scene* scene) : m_scene(scene), pixels(0)
{
    unsigned resx = m_scene->getResX();
    unsigned resy = m_scene->getResY();
    pixels = (unsigned char*) malloc(resx*resy*3*sizeof(unsigned char));
    m_restart = false;
    m_drawNormals = false;
    m_drawAmbient = true;
    m_drawDiffuse = true;
    m_drawSpecular = true;
    m_drawIndirect = true;
    m_subpixels = 1;
}

RenderAlg::~RenderAlg()
{
    if(pixels)
        free(pixels);
    pixels = 0;
}

std::vector<Ray> RenderAlg::raysFromCamera()
{
	unsigned resx = m_scene->getResX();
	unsigned resy = m_scene->getResY();

    Scalar width = m_scene->getWidth();
    Scalar height = m_scene->getHeight();

    Scalar pixelWidth = width/resx;
    Scalar pixelHeight = height/resy;
    Vector3& camera = m_scene->getCameraPosition();
    Vector3& camDir = m_scene->getCameraDirection();
    Vector3 camUp = m_scene->getCameraUp();
    camUp *= -1;
    Vector3 camSide = Vector3::crossProd(camUp, camDir);

    Scalar subpixelWidth = pixelWidth/(Scalar)m_subpixels;
    Scalar subpixelHeight = pixelHeight/(Scalar)m_subpixels;


    Vector3 positionCorner;
    Vector3 midScreen = camera + camDir*m_scene->getNear();
    positionCorner = midScreen - camUp*(height/2.0) - camSide*(width/2.0);

	std::vector<Ray> result;

    for(int sx = 0; sx < m_subpixels; ++sx)
    {
        for(int sy = 0; sy < m_subpixels; ++sy)
        {
            for (int x = 0; x < resx; ++x)
            {
                for (int y = 0; y < resy; ++y)
                {
                    Vector3 posPixel = positionCorner + camSide*pixelWidth*x + camUp*pixelHeight*y;
                    posPixel += camSide*sx*subpixelWidth + camUp*sy*subpixelHeight;
                    Ray r;
                    r.origin = camera;
                    r.direction = posPixel - camera;
                    r.direction.normalize();
                    result.push_back(r);
                }
            }
        }
    }
    return result;
}

void RenderAlg::writeToFile(string filename)
{
    unsigned resx = m_scene->getResX();
    unsigned resy = m_scene->getResY();

    cout << "Write to file " << filename << endl;
    QImage image(( unsigned char*)pixels, resx, resy, QImage::Format_RGB888);
    image.save(filename.c_str());
}




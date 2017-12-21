#include "DirectIllumination.h"
#include "Scene.h"

DirectIllumination::DirectIllumination(Scene *scene)
    : RenderAlg(scene)
{

}

Vector3 DirectIllumination::getDirectIllumination(Vector3 point, Vector3 normal, Material mat)
{
    Vector3 col = Vector3::ZERO;
    for(int l=0; l < m_scene->getLights().size(); ++l)
    {
        Light* light = m_scene->getLights()[l];
        vector<Vector3> samples = light->getSamples();
        for(int s=0; s<samples.size(); ++s)
        {
            Vector3 L = samples[s] - point;
            L.normalize();

            Ray rShadow(point, L);
            Vector3 pointShadow, normalShadow;
            Material matShadow;
            Object *objShadow = 0;
            bool isLight;
            bool shadow = m_scene->getFirstIntersectionPoint(rShadow, &objShadow, pointShadow, normalShadow, matShadow, isLight);
            if(shadow && !isLight && Vector3::squaredDistance(pointShadow, point) <
                    Vector3::squaredDistance(point, samples[s]))
                continue;

            Scalar dotLN = Vector3::dotProd(L, normal);
            if(dotLN > 0 && m_drawDiffuse)
                col += (mat.diffuse * dotLN * light->getDiffuse()) * (1.0/samples.size());

            Vector3 V = m_scene->getCameraPosition() - point;
            Vector3 R = 2*dotLN * normal - L;
            R.normalize();
            V.normalize();
            Scalar dotRV = Vector3::dotProd(R, V);
            if(dotRV > 0 && dotLN > 0 && m_drawSpecular)
                col += (mat.specular * pow(dotRV, mat.shininess) * light->getSpecular()) * (1.0/samples.size());
        }
    }
    return col;
}

void DirectIllumination::process()
{
    unsigned resx = m_scene->getResX();
    unsigned resy = m_scene->getResY();


//    memset(pixels, 0, resx*resy*3*sizeof(unsigned char));

    std::vector<Ray> rays = raysFromCamera();

    int r=0;
    int percentage = 0;
    for (int i = 0; i < resx; ++i)
    {
        for (int j = 0; j < resy; ++j)
        {
            if(m_restart)
            {
                i = 0;
                j = 0;
                r = 0;
                percentage = 0;
                m_restart = false;
            }

            if(floor((100*r)/rays.size()) > percentage)
            {
                percentage = floor((100*r)/rays.size());
                cerr<<percentage<<"% \r";

            }

            if(i == 315 && j == 114)
                cout << "here" << endl;

            Vector3 point, normal;
            Material mat;
            Object *obj = 0;
            bool isLight;
            if(m_scene->getFirstIntersectionPoint(rays[r++], &obj, point, normal, mat, isLight))
            {


                if(isLight)
                {
                    pixels[(j*resx+i)*3+0] = (unsigned char) floor(mat.diffuse[0]*255);
                    pixels[(j*resx+i)*3+1] = (unsigned char) floor(mat.diffuse[1]*255);
                    pixels[(j*resx+i)*3+2] = (unsigned char) floor(mat.diffuse[2]*255);
                    continue;
                }

                Vector3 col = Vector3::ZERO;
                if(m_drawNormals)
                {
                    col = normal;
                    col[0] = (col[0]+1)/2;
                    col[1] = (col[1]+1)/2;
                    col[2] = (-col[2]+1)/2;

                    col[0] = max(min(col[0], 1.0), 0.0);
                    col[1] = max(min(col[1], 1.0), 0.0);
                    col[2] = max(min(col[2], 1.0), 0.0);

                    pixels[(j*resx+i)*3+0] = (unsigned char) floor(col[0]*255);
                    pixels[(j*resx+i)*3+1] = (unsigned char) floor(col[1]*255);
                    pixels[(j*resx+i)*3+2] = (unsigned char) floor(col[2]*255);
                    continue;
                }

//                if(obj->m_name == "sphere")
//                    cout << "sphere" << endl;


                if(m_drawAmbient)
                    col = mat.ambient * m_scene->getAmbient();

                col += getDirectIllumination(point, normal, mat);


                col[0] = max(min(col[0], 1.0), 0.0);
                col[1] = max(min(col[1], 1.0), 0.0);
                col[2] = max(min(col[2], 1.0), 0.0);

                pixels[(j*resx+i)*3+0] = (unsigned char) floor(col[0]*255);
                pixels[(j*resx+i)*3+1] = (unsigned char) floor(col[1]*255);
                pixels[(j*resx+i)*3+2] = (unsigned char) floor(col[2]*255);
            }
        }
    }

    emit finished();
}

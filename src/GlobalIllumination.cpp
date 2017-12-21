#include <omp.h>
#include <OpenEXR/ImathQuat.h>

#include "GlobalIllumination.h"
#include "Scene.h"



GlobalIllumination::GlobalIllumination(Scene *scene)
    : RenderAlg(scene)
{
    srand48(time(0));
    m_maxDepth = 1;
    m_numBounceDirections = 5;
}

vector<Ray> GlobalIllumination::getRandomDirectionsHemisphere(Vector3 point, Vector3 normal, int numDirections)
{
    vector<Ray> rays;

    normal.normalize();
    Vector3 y = Vector3::UNIT_Y;

    Quaternion q = Quaternion::FromVectorToVector(y, normal);

    //    Imath::V3f inormal(normal[0], normal[1], normal[2]);
    //    Imath::V3f iy(0,1,0);
    //    Imath::Quatf iq;
    //    iq.setRotation(iy, inormal);

    //    cout << q.w << " " << q.x << " " << q.y << " " << q.z << endl;
    //    cout << iq.r << " " << iq.v[0] << " " << iq.v[1] << " " << iq.v[2] << endl;

    Matrix33 rot = q.ToRotationMatrix();

    for(int i=0; i<numDirections; ++i)
    {
        Ray r;
        r.origin = point;
        Scalar azimuthal = 2*M_PI*drand48();
        Scalar zenith = asin(sqrt(drand48()));

        // Calculate the cartesian point
        r.direction[0] = sin(zenith)*cos(azimuthal);
        r.direction[1] = cos(zenith);
        r.direction[2] = sin(zenith)*sin(azimuthal);

        r.direction = rot*r.direction;
        r.direction.normalize();

        rays.push_back(r);
    }
    return rays;
}

Vector3 GlobalIllumination::getDirectIllumination(Vector3 point, Vector3 normal, Material mat)
{
    Vector3 col = Vector3::ZERO;

    if(m_drawAmbient)
        col = mat.ambient * m_scene->getAmbient();

    for(int l=0; l < m_scene->getLights().size(); ++l)
    {
        Light* light = m_scene->getLights()[l];
        vector<Vector3> samples = light->getSamples();
        for(int s=0; s<samples.size(); ++s)
        {
            Vector3 L = samples[s] - point;
            Scalar distanceLP = L.getSquaredLength();
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
            //                col += (mat.diffuse * (dotLN/(distanceLP*0.1)) * light->getDiffuse()) * (1.0/samples.size());

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

Vector3 GlobalIllumination::getIndirectIllumination(Vector3 point, Vector3 normal, Material mat, int depth)
{
    Vector3 indirectDiffuse = Vector3::ZERO;
    if(depth >= m_maxDepth)
        return indirectDiffuse;

    vector<Ray> rays = getRandomDirectionsHemisphere(point, normal, m_numBounceDirections);

    for(int i=0; i<rays.size(); ++i)
    {
        Vector3 rPoint, rNormal;
        Material rMaterial;
        Object *obj;
        bool isLight;
        if(m_scene->getFirstIntersectionPoint(rays[i], &obj, rPoint, rNormal, rMaterial, isLight))
        {

            if(isLight)
                continue;

            Vector3 rcol = getDirectIllumination(rPoint, rNormal, rMaterial);

            Vector3 L = rPoint - point;
            L.normalize();

            Scalar dotLN = Vector3::dotProd(L, normal);
            if(dotLN > 0)
                indirectDiffuse += (mat.diffuse * dotLN * rcol) * (1.0 / 2 * M_PI);
        }
    }

    indirectDiffuse *= 1.0/rays.size();
    return indirectDiffuse;
}

void GlobalIllumination::process()
{
    QTime myTimer;
    myTimer.start();

    unsigned resx = m_scene->getResX();
    unsigned resy = m_scene->getResY();


    std::vector<Ray> rays = raysFromCamera();

    int numPixels = resx*resy;

    do
    {
        m_restart = false;
        int percentage = 0;
        int numRaysProcessed = 0;

        int numSubpixels = pow(m_subpixels, 2);
        memset(pixels, 0, resx*resy*3*sizeof(unsigned char));

        #pragma omp parallel for
        for (int r = 0; r < numPixels; ++r)
        {
            int i = floor(r / resx);
            int j = r % resy;

            Vector3 col = Vector3::ZERO;
            for(int s=0; s<numSubpixels; ++s)
            {

                if(m_restart)
                    continue;

//                if(omp_get_thread_num() == 0)
//                {
//                    int theadNumPixels = numPixels / omp_get_num_threads();

//                    if(floor((100*numRaysProcessed++)/theadNumPixels) > percentage)
//                    {
//                        percentage = floor((100*r)/theadNumPixels);
//                        cerr<<percentage<<"% \r";

//                    }
//                }

//                if(i == 315 && j == 114)
//                    cout << "here" << endl;

                Vector3 point, normal;
                Material mat;
                Object *obj = 0;
                bool isLight;
                if(m_scene->getFirstIntersectionPoint(rays[s*numPixels+r], &obj, point, normal, mat, isLight))
                {
                    if(isLight)
                    {
                        col += mat.diffuse*(1.0/(Scalar)numSubpixels);
                        continue;
                    }


                    if(m_drawNormals)
                    {
                        col = normal;
                        col[0] = (col[0]+1)/2;
                        col[1] = (col[1]+1)/2;
                        col[2] = (-col[2]+1)/2;

                        col[0] = max(min(col[0], 1.0), 0.0);
                        col[1] = max(min(col[1], 1.0), 0.0);
                        col[2] = max(min(col[2], 1.0), 0.0);

                        continue;
                    }

    //                if(i == 14 && j == 254)
    //                    cout << "here" << endl;

                    Vector3 colSample = getDirectIllumination(point, normal, mat);

                    if(m_drawIndirect)
                        colSample += getIndirectIllumination(point, normal, mat, 1);

                    colSample[0] = max(min(colSample[0], 1.0), 0.0);
                    colSample[1] = max(min(colSample[1], 1.0), 0.0);
                    colSample[2] = max(min(colSample[2], 1.0), 0.0);

                    col += colSample * (1.0/numSubpixels);

//                    if(i == 16 && j == 84)
//                        cout << col[0]*numSubpixels << endl;


                }
            }
            pixels[(j*resx+i)*3+0] += (unsigned char) floor(col[0]*255.0);
            pixels[(j*resx+i)*3+1] += (unsigned char) floor(col[1]*255.0);
            pixels[(j*resx+i)*3+2] += (unsigned char) floor(col[2]*255.0);
        }
    } while(m_restart);

    emit finished();

    int msecs = myTimer.elapsed();
    cout << "Done in " << msecs/1000 << " seconds" << endl;
}

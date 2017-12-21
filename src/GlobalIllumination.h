#ifndef GLOBALILLUMINATION_H
#define GLOBALILLUMINATION_H


#include "RenderAlg.h"
#include "Object.h"

class GlobalIllumination : public RenderAlg
{


public:
    GlobalIllumination(Scene* scene);

    vector<Ray> getRandomDirectionsHemisphere(Vector3 point, Vector3 normal, int numDirections);

    Vector3 getDirectIllumination(Vector3 point, Vector3 normal, Material mat);

    Vector3 getIndirectIllumination(Vector3 point, Vector3 normal, Material mat, int depth);



public Q_SLOTS:
    void process();

};



#endif // GLOBALILLUMINATION_H

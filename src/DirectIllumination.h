#ifndef DIRECTLIGHTING_H
#define DIRECTLIGHTING_H

#include "RenderAlg.h"
#include "Object.h"

class DirectIllumination : public RenderAlg
{
public:
    DirectIllumination(Scene* scene);

    Vector3 getDirectIllumination(Vector3 point, Vector3 normal, Material mat);

public Q_SLOTS:
    void process();

};

#endif // DIRECTLIGHTING_H

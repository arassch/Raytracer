#ifndef __SCENE_H
#define __SCENE_H


#include "Definitions.h"
#include "Light.h"
#include "Object.h"

class Scene
{
    Vector3 m_cameraPosition;
    Vector3 m_cameraDirection;
    Vector3 m_cameraUp;
    Scalar m_near;
    Scalar m_width, m_height;
	unsigned m_resx, m_resy;
    std::vector<Object*> m_objects;
	std::vector<Light*> m_lights;
    Vector3 m_ambient;

public:
    Scene();

    void test1();
    void test2();
    void test3();
    void testMirror();
    void cornellScene();

	virtual ~Scene();



    Vector3 getAmbient() { return m_ambient; }

	unsigned getResX() { return m_resx; }
	unsigned getResY() { return m_resy; }

    Scalar getWidth() { return m_width; }
    Scalar getHeight() { return m_height; }

    Vector3& getCameraPosition() { return m_cameraPosition; }
    Vector3& getCameraDirection() { return m_cameraDirection; }
    Vector3& getCameraUp() { return m_cameraUp; }
    Scalar getNear() { return m_near; }


    bool getFirstIntersectionPoint(Ray& ray, Object **obj, Vector3& point, Vector3& normal, Material& material, bool &isLight);
    std::vector<Light *> getLights() const;
};


#endif

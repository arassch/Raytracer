#include "Scene.h"


Scene::Scene()
{
    m_cameraPosition.set(0,0,-15);
    m_cameraDirection.set(0,0,1);
    m_cameraUp.set(0,1,0);
	m_near = 5;

	m_width = m_height = 5;
    m_resx = 500, m_resy = 500;

//    test1();
//    test2();
//    test3();
//    testMirror();
    cornellScene();
}

void Scene::test1()
{
    m_ambient.set(.1,.1,.1);

    Material mWall;
    mWall.ambient.set(0.3,0.3,0.3);
    mWall.diffuse.set(0.8,0.8,0.8);
    mWall.specular.set(0.1,0.1,0.1);
    mWall.shininess = 60.0;

    Plane* wallBack = new Plane("wall", mWall, Vector3(0,0,4), Vector3(0,0,-1));
    m_objects.push_back(wallBack);


    Material mSphere;
    mSphere.ambient.set(0.3,0.3,0.3);
    mSphere.diffuse.set(0.9,0.5,0.5);
    mSphere.specular.set(0.6,0.6,0.6);
    mSphere.shininess = 60;

    Sphere* sphere = new Sphere("sphere", mSphere, Vector3(2,0,2), 2);
    m_objects.push_back(sphere);

    Material mMesh;
    mMesh.ambient.set(0.3,0.3,0.3);
    mMesh.diffuse.set(0.6,0.2,1);
    mMesh.specular.set(0.6,0.6,0.6);
    mMesh.shininess = 60;

//    Mesh* mesh = new Mesh("bunny", mMesh, "/Users/sarac.schvartzman/Dropbox/Code/bunny.obj", 40.0);
    Mesh* mesh = new Mesh("teapot", mMesh, "/Users/sarac.schvartzman/Dropbox/Code/teapot.obj", 1.0);
    m_objects.push_back(mesh);

    Material lightMat;
    lightMat.diffuse = Vector3(1,1,1);
    lightMat.specular = Vector3(1,1,1);
    PointLight* light = new PointLight(Vector3(-3,3,2), lightMat);
//    m_lights.push_back(light);
    PointLight* light2 = new PointLight(Vector3(5,1,-5), lightMat);
    m_lights.push_back(light2);
}

void Scene::test2()
{
    m_cameraPosition.set(0,0,-4);
    m_cameraDirection.set(0,0,1);
    m_cameraUp.set(0,1,0);
    m_near = 5;

    m_ambient.set(.1,.1,.1);

    Material mSphere;
    mSphere.ambient.set(0.3,0.3,0.3);
    mSphere.diffuse.set(0.9,0.5,0.5);
    mSphere.specular.set(0.6,0.6,0.6);
    mSphere.shininess = 60;

    Sphere* sphere = new Sphere("sphere", mSphere, Vector3(0,0,0), 1);
    m_objects.push_back(sphere);


    Material lightMat;
    lightMat.diffuse = Vector3(1,1,1);
    lightMat.specular = Vector3(1,1,1);
    PointLight* light = new PointLight(Vector3(1,4,1), lightMat);
    m_lights.push_back(light);

}

void Scene::test3()
{
    m_cameraPosition.set(0,0,-6);
    m_cameraDirection.set(0,0,1);
    m_cameraDirection.normalize();
    m_cameraUp.set(0,1,0);
    m_near = 5;

    m_ambient.set(.1,.1,.1);

    Material mSphere;
    mSphere.ambient.set(0.3,0.3,0.3);
    mSphere.diffuse.set(0.5,0.5,0.5);
    mSphere.specular.set(0.6,0.6,0.6);
    mSphere.shininess = 60;

    Sphere* sphere = new Sphere("sphere", mSphere, Vector3(0,0,0), 1);
    m_objects.push_back(sphere);


    Material mWall;
    mWall.ambient.set(0.3,0.3,0.3);
    mWall.diffuse.set(0.5,0.9,0.5);
    mWall.specular.set(0.1,0.1,0.1);
    mWall.shininess = 60.0;
    Plane *wall = new Plane("wall", mWall,
                                Vector3(2,0,0), Vector3(-1,0,0));

    Material mFloor;
    mFloor.ambient.set(0.3,0.3,0.3);
    mFloor.diffuse.set(0.9,0.5,0.5);
    mFloor.specular.set(0.1,0.1,0.1);
    mFloor.shininess = 60.0;
    m_objects.push_back(wall);

    Plane *floor = new Plane("floor", mFloor,
                                Vector3(0,-1,0), Vector3(0,1,0));
    m_objects.push_back(floor);


    Material lightMat;
    lightMat.diffuse = Vector3(1,1,1);
    lightMat.specular = Vector3(1,1,1);
    PointLight* light = new PointLight(Vector3(0,4,-1), lightMat);
    m_lights.push_back(light);
}

void Scene::testMirror()
{
    m_cameraPosition.set(0,0,-6);
    m_cameraDirection.set(0,0,1);
    m_cameraDirection.normalize();
    m_cameraUp.set(0,1,0);
    m_near = 5;

    m_ambient.set(.1,.1,.1);

    Material mSphere;
    mSphere.ambient.set(0.0,0.0,0.0);
    mSphere.diffuse.set(1.0,1.0,1.0);
    mSphere.specular.set(0,0,0);
    mSphere.shininess = 60;

    Sphere* sphere = new Sphere("sphere", mSphere, Vector3(0,0,0), 1);
    m_objects.push_back(sphere);


    Material mWall;
    mWall.ambient.set(0.3,0.3,0.3);
    mWall.diffuse.set(0.5,0.9,0.5);
    mWall.specular.set(0.1,0.1,0.1);
    mWall.shininess = 60.0;
    Plane *wall = new Plane("wall", mWall,
                                Vector3(2,0,0), Vector3(-1,0,0));

    Material mFloor;
    mFloor.ambient.set(0.3,0.3,0.3);
    mFloor.diffuse.set(0.9,0.5,0.5);
    mFloor.specular.set(0.1,0.1,0.1);
    mFloor.shininess = 60.0;
    m_objects.push_back(wall);

    Plane *floor = new Plane("floor", mFloor,
                                Vector3(0,-1,0), Vector3(0,1,0));
    m_objects.push_back(floor);


    Material lightMat;
    lightMat.diffuse = Vector3(1,1,1);
    lightMat.specular = Vector3(1,1,1);
    PointLight* light = new PointLight(Vector3(0,4,-1), lightMat);
    m_lights.push_back(light);
}

void Scene::cornellScene()
{
    m_cameraPosition.set(0, 1., 3);
    m_cameraDirection.set(0, 0, -1);
    m_cameraDirection.normalize();
    m_cameraUp.set(0,1,0);
    m_near = 5;

    m_ambient.set(.1,.1,.1);

    Material mWall, mBox, mLeftWall, mRightWall;
    mWall.ambient.set(0.3,0.3,0.3);
    mWall.diffuse.set(0.9,0.9,0.9);
    mWall.specular.set(0.1,0.1,0.1);
    mWall.shininess = 60.0;

    mLeftWall = mWall;
    mLeftWall.diffuse.set(0.9,0.5,0.5);

    mRightWall = mWall;
    mRightWall.diffuse.set(0.5,0.9,0.5);

    mBox.ambient.set(0.3,0.3,0.3);
    mBox.diffuse.set(0.9,0.5,0.5);
    mBox.specular.set(0.6,0.6,0.6);
    mBox.shininess = 60;

    Mesh* tallBox = new Mesh("tallBox", mWall, "/Users/sarac.schvartzman/Dropbox/Code/cornellBox/tallBox.obj", 1.0);
    m_objects.push_back(tallBox);

    Mesh* shortBox = new Mesh("shortBox", mWall, "/Users/sarac.schvartzman/Dropbox/Code/cornellBox/shortBox.obj", 1.0);
    m_objects.push_back(shortBox);


    Square *backWall = new Square("backWall", mWall,
                                Vector3(-1,0,-1), Vector3(1,0,-1), Vector3(-1,2,-1),
                                Vector3(0,0,1));
    m_objects.push_back(backWall);

    Square *floor = new Square("floor", mWall,
                                Vector3(1,0,1), Vector3(1,0,-1), Vector3(-1,0,1),
                                Vector3(0,1,0));
    m_objects.push_back(floor);

    Square *ceiling = new Square("ceiling", mWall,
                                Vector3(1,2,1), Vector3(1,2,-1), Vector3(-1,2,1),
                                Vector3(0,-1,0));
    m_objects.push_back(ceiling);

    Square *rightWall = new Square("rightWall", mRightWall,
                                Vector3(1,0,-1), Vector3(1,0,1), Vector3(1,2,-1),
                                Vector3(-1,0,0));
    m_objects.push_back(rightWall);

    Square *leftWall = new Square("leftWall", mLeftWall,
                                Vector3(-1,0,-1), Vector3(-1,0,1), Vector3(-1,2,-1),
                                Vector3(1,0,0));
    m_objects.push_back(leftWall);



    Material lightMat;
    lightMat.diffuse = Vector3(1,1,1);
    lightMat.specular = Vector3(1,1,1);
//    PointLight* light = new PointLight(Vector3(0,1,3), lightMat);
//    m_lights.push_back(light);

    SquareLight* light = new SquareLight(Square("light", mBox,
                                                Vector3(-0.15, 1.98, -0.15),
                                                Vector3(0.15, 1.98, -0.15),
                                                Vector3(-0.15, 1.98, 0.15),
                                                Vector3(0,-1,0)), 8, 8,
                                         lightMat);
    m_lights.push_back(light);
}

Scene::~Scene()
{
	for (int i = 0; i < m_objects.size(); ++i)
	{
		delete(m_objects[i]);
	}
	m_objects.clear();

	for (int i = 0; i < m_lights.size(); ++i)
	{
		delete(m_lights[i]);
	}
    m_lights.clear();
}



bool Scene::getFirstIntersectionPoint(Ray& ray, Object **obj, Vector3& point, Vector3& normal, Material &material, bool &isLight)
{
    Scalar minT = 999999;
    bool intersection = false;
	for (int i = 0; i < m_objects.size(); ++i)
	{ 
        Vector3 currentNormal;
        Scalar t;
        if(m_objects[i]->intersects(ray, t, currentNormal))
        {
            if(t > 0.0001 && t < minT)
            {
                intersection = true;
                minT = t;
                normal = currentNormal;
                material = m_objects[i]->getMaterial();
                *obj = m_objects[i];
            }
        }
	}

    isLight = false;
    for (int i = 0; i < m_lights.size(); ++i)
    {
        Scalar t;
        if(m_lights[i]->intersects(ray, t))
        {
            if(t > 0.001 && t < minT)
            {
                intersection = true;
                minT = t;
                material = m_lights[i]->getMaterial();
                *obj = m_lights[i]->getObject();
                isLight = true;
            }
        }
    }

    if(intersection)
        point = ray.pointAt(minT);
    return intersection;
}

std::vector<Light *> Scene::getLights() const
{
    return m_lights;
}




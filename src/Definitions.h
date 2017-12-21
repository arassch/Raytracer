#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <QTime>

#include <Vector3.h>
using namespace std;
using namespace LA;

#define Scalar double

struct Ray
{
    Vector3 origin;
    Vector3 direction;

    Ray() {}
    Ray(Vector3 o, Vector3 d) : origin(o), direction(d) {}
    Vector3 pointAt(Scalar t) { return origin + t*direction; }
};

#endif

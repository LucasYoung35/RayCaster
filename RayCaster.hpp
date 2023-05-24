#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "Vec.hpp"

class Ray{
    public:
        Vec origin;
        Vec direction;
};

class Color{
    public:
        unsigned char R;
        unsigned char G;
        unsigned char B;
};

class Sphere{
    public:
        Vec center;
        double radius;
};

class Obj{
    public:
        Sphere sphere;
        Color color;
        Obj *next;
};

#endif
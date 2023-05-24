#ifndef VEC_H
#define VEC_H

class Vec{
        double x;
        double y;
        double z;
        void init(double, double, double);
    public:
        Vec(double, double, double);
        double getX();
        double getY();
        double getZ();
        void normalize();

};

#endif
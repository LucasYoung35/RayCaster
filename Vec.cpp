#include <cmath>

#include "Vec.hpp"

using namespace std;

//private init method assigns x, y, and z values
//called by public instructor
void Vec::init(double new_x, double new_y, double new_z){
    x=new_x;
    y=new_y;
    z=new_z;
}

//public constructor calls private init
Vec::Vec(double new_x, double new_y, double new_z){
    init(new_x, new_y, new_z);
}

//public method to access private x field
double Vec::getX(){
    return x;
}

//public method to access private y field
double Vec::getY(){
    return y;
}

//public method to access private z field
double Vec::getZ(){
    return z;
}

//computes and returns normalized vector 
void Vec::normalize(){

    //compute the magnitude of the vector
    double magnitude = sqrt((x*x)+(y*y)+(z*z));

    //compute normalize values
    x=x/magnitude;
    y=y/magnitude;
    z=z/magnitude;
}
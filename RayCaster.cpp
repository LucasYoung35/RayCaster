#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>

#include "Vec.hpp"
#include "RayCaster.hpp"

using namespace std;


//reads spheres from stdin; creates linked list using dynamic memory
void read_objs(Obj **list){

    double x;
    double y;
    double z;

    double radius;

    double r;
    double g;
    double b;

    bool head_filled=false;

    //read in sphere information from file
    while(scanf("%lf %lf %lf \n%lf \n%lf %lf %lf", &x, &y, &z, &radius, &r, &g, &b)!=EOF){
        
        //newest obj to be input
        Obj *new_obj = (Obj*)malloc(sizeof(*new_obj));

        //center of sphere
        Vec center(x,y,z);

        //sphere and color to be used in obj_t
        Sphere sphere{center, radius};

        Color color{(unsigned char)(255*r), (unsigned char)(255*g), (unsigned char)(255*b)};

        //store information in new_obj
        new_obj->color = color;
        new_obj->sphere = sphere;

        //if there is nothing at the head, place obj at head
        //else make obj new head and obj-> is the old head
        if(!head_filled){
            *list = new_obj;
            head_filled=true;
        }
        else{
            new_obj->next=*list;
            *list=new_obj;
        }


    }

}

//computes intersection of ray and sphere; returns 1 if intersection, 0 otherwise; t is set to
//distance from camera to sphere intersection
int intersect_sphere(Ray ray, Sphere sphere, double *t){

    //coefficients for quadratic formula
    double A = 1;

    double B = 2 * (ray.direction.getX() * (ray.origin.getX()-sphere.center.getX()) + 
                    ray.direction.getY() * (ray.origin.getY()-sphere.center.getY()) + 
                    ray.direction.getZ() * (ray.origin.getZ()-sphere.center.getZ()));

    double C = (ray.origin.getX()-sphere.center.getX()) * (ray.origin.getX()-sphere.center.getX()) + 
               (ray.origin.getY()-sphere.center.getY()) * (ray.origin.getY()-sphere.center.getY()) + 
               (ray.origin.getZ()-sphere.center.getZ()) * (ray.origin.getZ()-sphere.center.getZ()) - 
               sphere.radius * sphere.radius;

    //check if discriminant is negative
    double discriminant = B*B-4*A*C;
    if(discriminant<0)
        return 0;
    
    double t_zero = (-B+sqrt(discriminant))/2*A;
    double t_one = (-B-sqrt(discriminant))/2*A;

    //check if sphere is in view
    if(t_zero < 0 || t_one < 0){
        return 0;
    }

    //return the closer position
    if(t_zero<=t_one){
        *t=t_zero;
        return 1;
    }else{
        *t=t_one;
        return 1;
    }
}

//iterates through linked list; finds closest intersection using intersect_sphere;
//returns color of closest sphere
Color cast(Ray ray, Obj *list){

    //values to hold the closest sphere information
    double closest_distance=-1;
    Color closest_color{0, 0, 0};

    //loop through list
    while(list != NULL){

        //double pointer to hold distance to closest sphere
        double *t = new double;

        //check for intersection
        if(intersect_sphere(ray, list->sphere, t)==1){  

            //if no previous intersection was made, then this sphere is the closest
            if(closest_distance==-1){
                closest_distance = *t;
                closest_color = list->color;
            }


            //check if this sphere is the closest;
            int s = *t;
            if(s<closest_distance){
                closest_distance = *t;
                closest_color = list->color;
            }



        }

        list = list->next;
    }


    return closest_color;
}

//calls read_objs; initializes image file; loops through pixels: sets ray, calls cast, prints
//pixel; frees linked list
int main (void){

    //*list points to the first obj in the linked list
    Obj ** list = new Obj*;

    read_objs(list);

   //print ppm header
    cout << "P6\n";
    cout << "1000 1000\n";
    cout << "255\n";

    //making a 1000 x 1000 image
    for(int y=0;y<1000;y++){
        for(int x=0;x<1000;x++){

            //set origin of the ray
            Vec origin(0,0,0);

            //set direction of the ray
            Vec direction(-0.5 + (x/1000.0), 0.5 - (y/1000.0), 1);
            direction.normalize();

            //ray to be casted
            Ray ray{origin, direction};

            //cast the ray and store color
            Color pix_color = cast(ray, *list);

            //print pixel color
            cout << pix_color.R << pix_color.G << pix_color.B;
        }
    }

    delete list;

    return 0;
}
//point.hpp

#ifndef _POINT_H
#define _POINT_H

#include <iostream>
#include <math.h>
#include <ctgmath>
#include "constants.hpp"

using namespace std;

class Point
//defines a 2-dimensional vector with some basic trig functions
{
public:
    //constructor
    Point();
    
    //getters
    float getX();
    float getY();
    float angle();              //returns the angle of the vector
    float magnitude();          //returns the magnitude of the vector
    float distance(Point p);   //returns the distance between two points
    
    //setters
    void set(float a, float b);
    void setX(float a);
    void setY(float a);
    void addX(float a);
    void addY(float a);
    void resize(float length);  //resizes a vector to a set size
    void mapToCircle();         //maps from square to a circle
    
private:
    float x, y;
};

#endif
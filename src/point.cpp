 //point.cpp

#include "header/point.hpp"

Point::Point()
{
    x = 0;
    y = 0;
}

float Point::getX() { return x; }

float Point::getY() { return y; }

float Point::angle()
{
    if (x != 0)
        return atan(y/x)*(180/pi);
    return  0;
}

float Point::magnitude() { return sqrt(pow(x, 2.0) + pow(y, 2.0)); }

float Point::distance(Point p) { return sqrt(pow(p.getX()-x, 2) + pow(p.getY()-y, 2)); }

void Point::set(float a, float b) { x = a; y = b; }

void Point::setX(float a) { x = a; }

void Point::setY(float a) { y = a; }

void Point::addX(float a) { x += a; }

void Point::addY(float a) { y += a; }

void Point::resize(float length)
{
    float m = magnitude();
    if (m > 0)
    {
        x = x/m * length;
        y = y/m * length;
    }
}

void Point::mapToCircle()
{
    int m = magnitude();    //save old magnitude
    if (m != 0)
    {
        //cout << x << " " << y << endl;
        float xSquare = x / m;      //temp variables
        float ySquare = y / m;
        //cout << xSquare << " " << ySquare << endl;
        x = xSquare * sqrt(1.0 - 0.5 * (pow(ySquare, 2.0)));   //map
        y = ySquare * sqrt(1.0 - 0.5 * (pow(xSquare, 2.0)));
        x = x * m;
        y = y * m;
    }
    
}
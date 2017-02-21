//bar.hpp

#ifndef _BAR_H
#define _BAR_H

#include "constants.hpp"
#include "graphic.hpp"

class Bar : public Graphic
{
public:
    Bar();
    void update(int h);
    
private:
    int value;      //current value
    int max;        //maximum value
};

class HealthBar : public Bar
{
public:
    HealthBar();
};

class StaminaBar : public Bar
{
public:
    StaminaBar();
};

#endif

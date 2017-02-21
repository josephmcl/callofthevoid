//bar.cpp

#include "header/bar.hpp"

Bar::Bar()
{
    value = 100;
    max = 100;
}

void Bar::update(int h)
{
    value = h;
    setPos(getFrame()->getX(), getFrame()->getY(), 80*value/max, 10);
}

HealthBar::HealthBar()
{
    Frame f = Frame(0, 0, 0, 80, 10, 0, 0, 80, 10, SHEET_UI);
    addFrame(f);
}

StaminaBar::StaminaBar()
{
    Frame f = Frame(0, 0, 0, 80, 10, 0, 32, 80, 10, SHEET_UI);
    addFrame(f);
}
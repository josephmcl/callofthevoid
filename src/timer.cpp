//timer.cpp

#include "header/timer.hpp"

Timer::Timer()
{
    delta = 0;
    past = 0;
    present = 0;
}

void Timer::update()
{
    past = present;
    present = SDL_GetTicks();
    delta = (present-past)/1000.0f;
    framerate = 1/delta;
}

float Timer::getTime() { return present; }

float Timer::getDelta() { return delta; }

float Timer::getFR() { return framerate; }
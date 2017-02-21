//utility.cpp

#include <tgmath.h>
#include "header/utility.hpp"

SDL_Rect rect(int x, int y, int h, int w)
//for initializing SDL's rectangle object
{
    SDL_Rect r = {x, y, h, w};
    return r;
}

SDL_Rect rect_mult(SDL_Rect r, int ratio)
{
    r.x = r.x * ratio;
    r.y = r.y * ratio;
    r.w = r.w * ratio;
    r.h = r.h * ratio;
    return r;
}
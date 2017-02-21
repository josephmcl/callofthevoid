//utility.hpp

#ifndef _UTILITY_H
#define _UTILITY_H

#include <SDL2/SDL.h>

SDL_Rect rect(int x, int y, int h, int w);
//for initializing SDL's rectangle object

SDL_Rect rect_mult(SDL_Rect r, int ratio);
//multiply an SDL rectangle's dimensions by a value

#endif
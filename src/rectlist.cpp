//rectlist.cpp

#include "header/rectlist.hpp"

void RectList::addRect(int x, int y, int w, int h)
{
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    rects.push_back(r);
}

void RectList::clear() { rects.clear(); }

unsigned long int RectList::getSize() { return rects.size(); }

SDL_Rect RectList::getRect(int n)
{
    if (n < rects.size())
        return rects.at(n);
    else
    {
        SDL_Rect temp;
        return temp;
    }
}
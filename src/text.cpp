//text.cpp

#include "header/text.hpp"

Text::Text(string val, int x, int y, int w, int h, int r, int g, int b)
{
    value = val;
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
    col.r = r;
    col.g = g;
    col.b = b;
    col.a = 255;
}

string Text::getValue() { return value; }

SDL_Rect Text::getPos() { return pos; }

SDL_Color Text::getCol() { return col; }

void Text::setValue(string val) { value = val; }

void Text::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Text::setPos(int x, int y, int w, int h)
{
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
}

void Text::setCol(int r, int g, int b)
{
    col.r = r;
    col.g = g;
    col.b = b;
}
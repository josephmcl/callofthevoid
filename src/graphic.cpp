//graphic.cpp

#include "header/graphic.hpp"

Graphic::Graphic()
{
    frameRate = 10;
    currentFrame = 0;
}

Graphic::Graphic(int delayTime, int pos_x, int pos_y, int pos_width, int pos_height,
        int crop_x, int crop_y, int crop_width, int crop_height, int sheet_id)
{
    frameRate = 10;
    currentFrame = 0;
    untilNext = 1000;

    Frame f = Frame(delayTime, pos_x, pos_y, pos_width, pos_height,
        crop_x, crop_y, crop_width, crop_height, sheet_id);
    animation.push_back(f);
}

void Graphic::update(Timer* timer)
{
    //TODO animation
}

Frame* Graphic::getFrame()
{
    if (currentFrame < animation.size())
        return &animation[currentFrame];
    else return new Frame();
}

void Graphic::setFrameRate(int i) { frameRate = i; }

void Graphic::addFrame(Frame& f) { animation.push_back(f); }

void Graphic::setPos(int x, int y)
{
    if (currentFrame < animation.size())
        animation[currentFrame].setPos(x, y);
}

void Graphic::setPos(int x, int y, int w, int h)
{
    if (currentFrame < animation.size())
        animation[currentFrame].setPos(x, y, w, h);
}

void Graphic::setPos(SDL_Rect& r)
{
    if (currentFrame < animation.size())
        animation[currentFrame].setPos(r);
}

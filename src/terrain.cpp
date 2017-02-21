//terrain.cpp

#include "header/terrain.hpp"

Terrain::Terrain()
{
    frameRate = 10;
    currentFrame = 0;
    untilNext = 1000;
}

Terrain::Terrain(int delayTime, int pos_x, int pos_y, int pos_width, int pos_height,
        int crop_x, int crop_y, int crop_width, int crop_height, int sheet_id)
{
    frameRate = 10;
    currentFrame = 0;
    untilNext = 1000;

    Frame f = Frame(delayTime, pos_x, pos_y, pos_width, pos_height,
        crop_x, crop_y, crop_width, crop_height, sheet_id);
    animation.push_back(f);
}

void Terrain::update(Timer* timer)
{
    
}

Frame* Terrain::getFrame()
{
    if (currentFrame < animation.size())
        return &animation[currentFrame];
    else return nullptr;
}

void Terrain::setFrameRate(int i) { frameRate = i; }

void Terrain::addFrame(Frame& f) { animation.push_back(f); }

//terrain.hpp

#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "timer.hpp"
#include "frame.hpp"
#include "hasframe.hpp"

class Terrain : public HasFrame
//for displaying UI elements
{
public:
    //constructors
    Terrain();
    Terrain(int delayTime, int pos_x, int pos_y, int pos_width, int pos_height,
        int crop_x, int crop_y, int crop_width, int crop_height, int sheet_id);
    
    //update function
    void update(Timer* timer);
    
    //getters
    Frame* getFrame();
    
    //setters
    void setFrameRate(int i);
    void addFrame(Frame& f);
    
private:
    vector < Frame > animation;
    int frameRate;              //animation speed. 0 to stop playing.
    int currentFrame;           //what frame are we on
    int untilNext;              //time until next frame
};

#endif

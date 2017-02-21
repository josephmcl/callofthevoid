//graphic.hpp

#ifndef _GRAPHIC_H
#define _GRAPHIC_H

#include "timer.hpp"
#include "frame.hpp"
#include "hasframe.hpp"

class Graphic : public HasFrame
//for displaying UI elements
{
public:
    //constructors
    Graphic();
    Graphic(int delayTime, int pos_x, int pos_y, int pos_width, int pos_height,
        int crop_x, int crop_y, int crop_width, int crop_height, int sheet_id);
    
    //update function
    void update(Timer* timer);
    
    //getters
    Frame* getFrame();
    
    //setters
    void setFrameRate(int i);
    void addFrame(Frame& f);
    void setPos(int x, int y);
    void setPos(int x, int y, int w, int h);
    void setPos(SDL_Rect &r);
    
private:
    vector < Frame > animation;
    int frameRate;              //animation speed. 0 to stop playing.
    int currentFrame;           //what frame are we on
    int untilNext;              //time until next frame
};

#endif


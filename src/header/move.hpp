//move.hpp

#ifndef _PIZZA_H
#define _PIZZA_H

#include "frame.hpp"

class Move
//animation for one of a fighter's moves in a given direction
{
public:    
    void addFrame(Frame* f);        //adds a frame
    Frame* getFrame(int i);         //returns a pointer to the requested frame
    Frame* back();                  //returns a pointer to the last frame
    unsigned long int size();       //returns number of frames in the animation
    
private:
    vector <Frame> frame;
};

#endif

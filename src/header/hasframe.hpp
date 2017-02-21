//hasFrame.hpp

#ifndef _HASFRAME_H
#define _HASFRAME_H

#include <iostream> //todo delete this
#include "frame.hpp"

class HasFrame
//virtual class used for any objects that have contain a frame
//these objects can vary in their draw order, or "depth", on the screen
{
public:
    //virtual method
    virtual Frame* getFrame() {return new Frame;}
};

#endif
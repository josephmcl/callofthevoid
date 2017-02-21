//move.cpp

#include "header/move.hpp"

void Move::addFrame(Frame* f) { frame.push_back(*f); }

Frame* Move::getFrame(int i)
{
    if (i < size())
        return &frame.at(i);
    else return new Frame();
}

Frame* Move::back()
{
    if (size() > 0)
        return &frame.back();
    else return new Frame();
}

unsigned long int Move::size() { return frame.size(); }

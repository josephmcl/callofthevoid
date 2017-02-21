//rectlist.hpp

#ifndef _RECTLIST_H
#define _RECTLIST_H

#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class RectList
//stores a vector of SDL rectangles
//useful for passing around lists of hit/punish/stand boxes
{
public:
    //constructors and destructors
    RectList(){};
    
    //setters
    void addRect(int x, int y, int w, int h);
    void clear();
    
    //getters
    unsigned long int getSize();
    SDL_Rect getRect(int n); //getrekt
    
private:
    vector <SDL_Rect> rects;
};

#endif
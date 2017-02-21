//
//  text.hpp
//  Call of the Void
//
//  Created by Gabe Branton on 5/27/16.
//  Copyright (c) 2016 Orstein and Code. All rights reserved.
//

#ifndef _TEXT_H
#define _TEXT_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

class Text
{
public:
    //constructor
    Text(){}
    Text(string val, int x, int y, int w, int h, int r, int g, int b);
        //constructs with a string value, x/y position, width, height, and an rgb color
    
    //getters
    string getValue();
    SDL_Rect getPos();
    SDL_Color getCol();
    
    //setters
    void setValue(string val);
    void setPos(int x, int y);
    void setPos(int x, int y, int w, int h);
    void setCol(int r, int g, int b);
    
private:
    string value;
    SDL_Rect pos;
    SDL_Color col;
};


#endif

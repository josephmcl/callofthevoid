//window.hpp

#ifndef _WINDOW_H
#define _WINDOW_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "utility.hpp"
#include "frame.hpp"
#include "text.hpp"

using namespace std;

////////////////////////////////////////

class Window
//responsible for all graphics handling
//capable of drawing frames, text and shapes
{
public:
    //constructors and destructors
    Window();
    ~Window();
    
    //update methods
    void clear();                   //clear the screen
    void draw(Frame* frame);        //draw a frame
    void draw(Text* text);          //draw some text
    void render();                  //render everything to the screen
    
    //getters
    bool getLoadSuccess();
    
    //setters
    void addTexture(string path, int id);

private:
    //SDL objects
    SDL_Window* window;
    SDL_Renderer* renderer;
    vector < SDL_Texture* > texture;
    vector < int > texture_id;
    TTF_Font* font;
    
    //for drawing frames
    SDL_Rect pos;
    SDL_Rect crop;
    
    //for drawing text
    SDL_Surface *textSurface;
    SDL_Texture *textTexture;
    
    //internal variables
    bool loadSuccess;
};

#endif

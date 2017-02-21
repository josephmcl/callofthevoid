//gamestate.hpp

#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "window.hpp"

class GameState
//virtual class for handling the three major functional modules
//of the game loop: talking to the event handler for user input,
//handling game logic and rendering to the window
{
public:
    //virtual methods
    virtual void events(){};
    virtual void logic(){};
    virtual void render(){};
    
    //getters
    bool getLoadSuccess();
    int getNextState();
    int getHumans();
    int getComputers();
    int getWinThresh();
    bool getMusic();
    bool getSFX();

    //window
    Window* window;
    void setWindow(Window* w);

    //variables
    bool loadSuccess;
    int nextState;
    int humans;
    int computers;
    int winThresh;
    bool music;
    bool sfx;
};

#endif
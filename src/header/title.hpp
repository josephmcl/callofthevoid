//title.hpp

#ifndef _TITLE_H
#define _TITLE_H

#include "utility.hpp"
#include "timer.hpp"
#include "eventhandler.hpp"
#include "graphic.hpp"
#include "text.hpp"
#include "gamestate.hpp"

class Title : public GameState
{
public:
    Title();
    
    void events();                  //handles all user input
    void logic();                   //handles all ongoing game logic
    void render();                  //handles all visual feedback
    
private:
    //game objects
    Timer timer;
    EventHandler eventhandler;
    
    //GUI objects
    Graphic logo;
    Graphic blackhole;
    Text start;
    Text quit;
    
    //variables
    short int select;               //0 for start game, 1 for exit
    float selectCooldown;       //time until we can change selection again
};

#endif

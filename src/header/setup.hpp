//setup.hpp

#ifndef _SETUP_HPP
#define _SETUP_HPP

#include "utility.hpp"
#include "timer.hpp"
#include "eventhandler.hpp"
#include "graphic.hpp"
#include "text.hpp"
#include "gamestate.hpp"

class SetUp : public GameState
{
public:
    SetUp();
    
    void events();                  //handles all user input
    void logic();                   //handles all ongoing game logic
    void render();                  //handles all visual feedback
    
private:
    //game objects
    Timer timer;
    EventHandler eventhandler;
    
    //GUI objects
    Text humansText;
    Text computersText;
    Text winThreshText;
    Text musicText;
    Text sfxText;
    Text startText;
    
    //variables
    short int select;               //0-5 for the 6 available options
    float selectCooldown;           //time until we can change selection again
};

#endif

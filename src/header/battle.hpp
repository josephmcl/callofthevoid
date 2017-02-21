//battle.hpp

#ifndef _BATTLE_H
#define _BATTLE_H

#include "constants.hpp"
#include "utility.hpp"
#include "eventhandler.hpp"
#include "audiohandler.hpp"
#include "hasframe.hpp"
#include "graphic.hpp"
#include "bar.hpp"
#include "terrain.hpp"
#include "maphandler.hpp"
#include "fighter.hpp"
#include "gamestate.hpp"

class Battle : public GameState
//represents a single round of the main game
{
public:
    //constructors and destructors
    Battle(){}
    Battle(int hmns, int cmptrs, int wins, bool musicToggle, bool sfxToggle, Map map);
    ~Battle();
    
    //overloaded methods
    void events();                  //handles all user input
    void logic();                   //handles all ongoing game logic
    void render();                  //handles all visual feedback
    
    //logic methods
    void handleCollisions();        //check for collisions and act on game objects accordingly
    
private:
    //game objects
    Timer timer;                //keeps track of time
    EventHandler eventhandler;  //keeps track of all user input
    AudioHandler audiohandler;  //responsible for all audio playback
    Fighter fighter[4];         //the combatants: each player controls one
    Graphic tiles[TILES_X_NUM][TILES_Y_NUM];    //the background is rendered from a set of tiles
    vector <Terrain> terrain;   //interactive foreground objects (trees, walls, traps, etc.)
    
    //GUI objects
    HealthBar healthbar[4];     //displays each player's health as a bar
    StaminaBar staminabar[4];   //displays each player's stamina as a bar
    Graphic target[4];          //arrows to indicate targetting (in order: red, blue, green, yellow)
    int targetID[4];            //indicates the target (-1 for no target, 0-3 otherwise)
    Graphic pauseSplash;        //the pause menu (not rendered unless we pause)
    
    //rendering
    vector < HasFrame* > renderOrder;   //sorted every frame in the order objects will be drawn
    
    //variables
    bool paused;                //is the game paused? (popcorn & beer break)
};

bool sortByY(HasFrame* lhs, HasFrame* rhs);

#endif
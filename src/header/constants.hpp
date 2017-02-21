//constants.hpp

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <math.h>
#include <ctgmath>

//window title
#define TITLE "Call of the Void v0.2"

////////////////////////////////////////////////////////////

//window dimensions
const int SCREEN_WIDTH = 960;       //width of the screen in pixels
const int SCREEN_HEIGHT = 540;      //height of the screen in pixels
const int PIXEL_RATIO = 2;          //actual size: 480x270
const int UI_HEIGHT = 46;           //user-interface height

//tiles
const int TILES_X = 16;             //size of background tiles
const int TILES_Y = 16;
const int TILES_X_NUM = 30;         //number of background tiles
const int TILES_Y_NUM = 14;

//debug
const bool SHOW_BOXES = false;       //show hit, punish and stand boxes

////////////////////////////////////////////////////////////

//game states (all states the top-level gamestate object can be in)
enum { STATE_NULL, STATE_TITLE, STATE_SETUP, STATE_BATTLE, STATE_EXIT };

//sprite sheets (names for all textures the game uses)
enum { SHEET_UI, SHEET_TITLE, SHEET_TILES, SHEET_TERRAIN, SHEET_KNIGHT };

//maps
enum Map { MAP_CASTLE, MAP_MAZE, MAP_ROOMS };

//moves (all actions the players can perform)
enum { MOVE_NONE, MOVE_WALK, MOVE_LIGHT_ATTACK, MOVE_ROLL, MOVE_BLOCK, MOVE_JUMP, MOVE_STUN, MOVE_PRONE };

//collision types (all types of collisions between objects with frames)
enum { STAND, HIT };

//directions (counterclockwise from southwest, matching the sprite sheet layout)
enum
{   SOUTHWEST
,   SOUTHEAST
,   EAST
,   NORTHEAST
,   NORTHWEST
,   WEST
};

//controller
const int JOYSTICK_DEAD_ZONE = 10000;   //no-input area at the center of each joystick
const int TAP_TIME = 200;               //how short a button press is to be registered as a tap
const int T_BUTTON = 10000;             //internal identifiers for controller buttons
const int O_BUTTON = 11000;
const int X_BUTTON = 12000;
const int S_BUTTON = 13000;
const int L1_BUTTON = 14000;
const int L2_BUTTON = 15000;
const int R1_BUTTON = 16000;
const int R2_BUTTON = 17000;
const int START_BUTTON = 18000;

//misc.
const float pi = (atan(1)*4);

#endif

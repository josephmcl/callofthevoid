/*
    Untitled Game for CIS 422
    By Gabriel Branton, Miles Chew, Joeseph McLaughlin, Jake Lin
*/

////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <ctgmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "header/constants.hpp"
#include "header/utility.hpp"
#include "header/point.hpp"
#include "header/timer.hpp"
#include "header/eventhandler.hpp"
#include "header/audiohandler.hpp"
#include "header/rectlist.hpp"
#include "header/frame.hpp"
#include "header/text.hpp"
#include "header/script.hpp"
#include "header/hasframe.hpp"
#include "header/graphic.hpp"
#include "header/bar.hpp"
#include "header/terrain.hpp"
#include "header/maphandler.hpp"
#include "header/move.hpp"
#include "header/fighter.hpp"
#include "header/window.hpp"
#include "header/gamestate.hpp"
#include "header/title.hpp"
#include "header/setup.hpp"
#include "header/battle.hpp"

using namespace std;

////////////////////////////////////////

//main.cpp

bool init()
//basic initialization
{
    //seed the random number generator
    srand((int)time(NULL));

    //initialize SDL
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
    {
        cout << "SDL Initialization Error" << endl;
        success = false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        cout << "PNG Load error: " << IMG_GetError() << endl;
        success = false;
    }
    if (TTF_Init() == -1)
    {
        cout << "SDL_ttf error: " << TTF_GetError() << endl;
        success = false;
    }
    
    return success;
}

void cleanup()
//closes SDL
{
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (init()) //initialize SDL
    {
        //create the window
        Window window;
        
        //create the first gamestate (the title screen) and pass the window to it
        GameState* gamestate = new Title();
        gamestate->setWindow(&window);
        
        //we change this when we want to change state
        int stateID = STATE_NULL;
        
        //did everything initialize properly?
        if (!(window.getLoadSuccess() && gamestate->getLoadSuccess()))
            stateID = STATE_EXIT;
        
        //main game loop
        while (stateID != STATE_EXIT)
        {
            //get user input
            gamestate->events();
            
            //do game logic
            gamestate->logic();
            
            //render to the screen
            gamestate->render();
            
            //change state
            stateID = gamestate->getNextState();
            if (stateID != STATE_NULL)
            {
                if (stateID != STATE_EXIT) delete gamestate; //delete the old gamestate
                switch (stateID)
                {
                    default:
                    case STATE_TITLE: //title
                        gamestate = new Title();
                        break;
                        
                    case STATE_SETUP: //set-up
                        gamestate = new SetUp();
                        break;

                    case STATE_BATTLE: //battle
                        int humans = gamestate->getHumans();
                        int computers = gamestate->getComputers();
                        int winThresh = gamestate->getWinThresh();
                        bool music = gamestate->getMusic();
                        bool sfx = gamestate->getSFX();
                        gamestate = new Battle(humans, computers, winThresh, music, sfx, MAP_CASTLE);
                        break;
                }
                gamestate->setWindow(&window); //pass window to new state
            }
            
        }
    }
    
    //exit
    cleanup(); //clean up SDL objects
    return 0;
}

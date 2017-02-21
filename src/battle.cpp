//battle.cpp

#include "header/battle.hpp"

Battle::Battle(int hmns, int cmptrs, int wins, bool musicToggle, bool sfxToggle, Map map)
{
    //initialize variables
    loadSuccess = true;
    nextState = STATE_NULL;
    paused = false;
    
    humans = hmns;
    computers = cmptrs;
    winThresh = wins;
    music = musicToggle;
    sfx = sfxToggle;
    
    //initialize audio
    audiohandler.loadSample("assets/swing.wav", "swing");
    audiohandler.loadSample("assets/shield_up.wav", "shield_up");
    audiohandler.loadSample("assets/shield_down.wav", "shield_down");
    audiohandler.loadSample("assets/roll.wav", "roll");
    audiohandler.loadSample("assets/rekt.wav", "rekt");
    audiohandler.loadSample("assets/target.wav", "target");
    audiohandler.loadSample("assets/untarget.wav", "untarget");
    
    //initialize fighter positions
    fighter[0].setPos(50,UI_HEIGHT+10);
    fighter[1].setPos(350, UI_HEIGHT+10);
    fighter[2].setPos(50, 200);
    fighter[3].setPos(350, 200);
    
    //how many players?
    for (int i = 0; i < humans + computers; i++)
    {
        if (i < 4)
        {
            fighter[i].setActive(true);
        }
    }
    
    //initialize map handler
    MapHandler maphandler;
    switch(map)
    {
        default:
        case MAP_CASTLE:
            if (!maphandler.loadMap("dat/castle-map.txt"))
                loadSuccess = false;
            break;
        case MAP_MAZE:
            if (!maphandler.loadMap("dat/maze-map.txt"))
                loadSuccess = false;
            break;
    }
    
    //initialize tiles
    while (maphandler.getYTile() < 14)
    {
        tiles[maphandler.getXTile()][maphandler.getYTile()] = maphandler.getNextTile();
    }
    
    //initialize terrain
    while (maphandler.getYTer() < 14)
    {
        Terrain temp = maphandler.getNextTerrain();
        if (temp.getFrame() != nullptr)
            terrain.push_back(temp);
    }

    //add fighters to RenderOrder
    for (int i = 0; i < 4; i++)
        renderOrder.push_back(&fighter[i]);
    
    //add terrain to RenderOrder
    for (int i = 0; i < terrain.size(); i++)
        renderOrder.push_back(&terrain[i]);
    
    //initialize health bar/stamina bar
    for (int i = 0; i < 4; i++)
    {
        healthbar[i].setPos(34 + 120*i, 19);
        staminabar[i].setPos(32 + 120*i, 30);
    }

    //initialize targetting arrows
    for (int i = 0; i < 4; i++)
    {
        target[i] = Graphic(0, 0, 0, 6, 4, 16*i, 80, 6, 4, SHEET_UI);
        targetID[i] = -1;
    }
    
    
    //initialize pause splash
    pauseSplash = Graphic(0, 120, 67, 240, 135, 80, 0, 240, 135, SHEET_UI);
}

Battle::~Battle()
{
    
}

void Battle::events()
{
    //update event handler
    eventhandler.update();
    
    //update audio handler
    audiohandler.update();

    //user closes window
    if (eventhandler.windowClosed())
        nextState = STATE_EXIT;
    
    if (paused) //if the game is paused, we have different controls
    {
        //navigating the menu with the controller
        for (int i = 0; i < 4; i++)
        {
            //unpausing the game
            if (eventhandler.buttonTapped(START_BUTTON, i))
                paused = false;
            
            //TODO moving cursor up and down the menu
            
            
            //TODO confirm selection
            
        }
    }
    else
    { //if the game is unpaused, we handle input normally
        //player input
        for (int i = 0; i < 4; i++)
        {
            //pausing the game (to access options, take a break, etc.)
            if (eventhandler.buttonTapped(START_BUTTON, i))
                paused = true;
        
            //movement
            fighter[i].setAcc(eventhandler.getXAxisLeft(i), eventhandler.getYAxisLeft(i));
            
            //targetting
            if (eventhandler.buttonTapped(S_BUTTON, i))
            {
                if (fighter[i].getHasTarget())
                {
                    //if we already have a target, we clear it
                    fighter[i].clearTarget();
                    audiohandler.playSample("untarget");
                    targetID[i] = -1;
                } else { //otherwise, we pick a target
                    short int closest = -1;
                    float distance = 10000; //start absurdly high
                    float newDistance = 0;
                    
                    //search through all players...
                    for (int j = 0; j < 4; j++)
                    if ((j != i) && (fighter[j].getActive())) //...that aren't us and that are also active...
                    {
                        newDistance = fighter[i].getPos().distance(fighter[j].getPos());
                        if (newDistance < distance)
                        {
                            //oh! this person is closer. they are our new candidate
                            distance = newDistance;
                            closest = j;
                        }
                    }
                    
                    //if we selected a good candidate, target them
                    if (closest != -1)
                    {
                        fighter[i].setTarget(&fighter[closest]);
                        audiohandler.playSample("target");
                        targetID[i] = closest;
                    }
                }
            }
            
            //light attack
            if (eventhandler.buttonHeld(R1_BUTTON, i, 0))
            {
                if (fighter[i].doMove(MOVE_LIGHT_ATTACK))
                    audiohandler.playSample("swing");
            }
            
            //roll
            if (eventhandler.buttonTapped(O_BUTTON, i))
            {
                if (fighter[i].doMove(MOVE_ROLL))
                    audiohandler.playSample("roll");
            }
            
            //block
            if (eventhandler.buttonHeld(L1_BUTTON, i, 50))
            {
                if (fighter[i].blockStart())
                    audiohandler.playSample("shield_up");
            } else {
                if(fighter[i].blockStop())
                    audiohandler.playSample("shield_down");
            }
        }
        
        //fighter[3].setPos(eventhandler.getXAxisLeft(0)+100, eventhandler.getYAxisLeft(0)+100); //TODO
    }
}

void Battle::logic()
{
    //update timer
    timer.update();
    
    if (!paused)
    {
        //update health/stamina bars
        for (int i = 0; i < 4; i++)
        {
            healthbar[i].update(fighter[i].getHP());
            staminabar[i].update(fighter[i].getSP());
        }
        
        //update fighters
        for (int i = 0; i < 4; i++) //for each fighter...
            if (fighter[i].getActive()) //is the fighter alive?
            {
                fighter[i].update(&timer); //update
            } else {
                //dead player cleanup
                targetID[i] = -1;
                for (int j = 0; j < 4; j++)
                {
                    if (targetID[j] == i)
                        targetID[j] = -1;
                }
            }
        
        //handle collisions
        handleCollisions();
    }
}

bool sortByY(HasFrame* lhs, HasFrame* rhs)
{
    return lhs->getFrame()->getY() + lhs->getFrame()->getStandY()
        < rhs->getFrame()->getY() + rhs->getFrame()->getStandY();
}

void Battle::render()
{
    //clear
    window->clear();
    
    //draw tiles
    for (int x = 0; x < TILES_X_NUM; x++)
    for (int y = 0; y < TILES_Y_NUM; y++)
        window->draw(tiles[x][y].getFrame());
    
    //sort and draw everything in renderOrder (fighters, terrain)
    sort(renderOrder.begin(), renderOrder.end(), sortByY);
    for (int i = 0; i < renderOrder.size(); i++)
    {
        window->draw(renderOrder.at(i)->getFrame());
    }
    
    //draw the player's magic shields
    for (int i = 0; i < 4; i++)
    {
        Frame* shield = fighter[i].getShieldFrame();
        if (shield != nullptr)
        {
            window->draw(shield);
        }
    }
    
    //draw health/stamina bars
    for (int i = 0; i < 4; i++)
    {
        window->draw(healthbar[i].getFrame());
        window->draw(staminabar[i].getFrame());
    }
    
    //draw targets as necessary
    for (int i = 0; i < 4; i++)
    {
        if (targetID[i] != -1) //if the target is visible...
        {
            //...position the target...
            target[i].setPos(fighter[targetID[i]].getPos().getX()+2, fighter[targetID[i]].getPos().getY()-10);
            //...and draw it
            window->draw(target[i].getFrame());
        }
    }
    
    //if paused, draw the pause splash
    if (paused)
    {
        window->draw(pauseSplash.getFrame());
        //TODO buttons
        //TODO selecter
    }
    
    //render everything
    window->render();
}

void Battle::handleCollisions()
{
    //collide fighters with each other
    for (int i = 0; i < 4; i++) //for each fighter...
        for (int j = 0; j < 4; j++) //...and each other fighter...
            if (i != j) //...if they are not the same fighter...
            {
                //stand collisions (fighters can't go through each other)
                if (fighter[i].getFrame()->collides(fighter[j].getFrame(), STAND))
                {
                    if (fighter[i].getActive() && fighter[j].getActive()) //are both alive?
                    {
                        fighter[i].revertPos();
                        fighter[j].revertPos();
                    }
                }
                //hit/punish collisions (for attacks)
                if (fighter[i].getFrame()->collides(fighter[j].getFrame(), HIT))
                    if (fighter[i].getActive() && fighter[j].getActive()) //are both alive?
                        if(fighter[j].hurt(20, fighter[i].getDir()))
                        {
                            audiohandler.playSample("rekt");
                        }
            }
    
    //collide fighters with terrain
    for (int i = 0; i < 4; i++) //for each fighter...
        for (int j = 0; j < terrain.size(); j++) //...and each piece of terrain...
            if (fighter[i].getFrame()->collides(terrain[j].getFrame(), STAND)) //...if their stand boxes collide...
                fighter[i].revertPos(); //...revert the position of the fighter
}

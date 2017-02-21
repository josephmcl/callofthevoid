//setup.cpp

#include "header/setup.hpp"

SetUp::SetUp()
{
    //initialize text
    humansText = Text("Human   Players    2", 80, 10, 300, 40, 120, 120, 120);
    computersText = Text("Computer   Players    0", 80, 45, 300, 40, 120, 120, 120);
    winThreshText = Text("Win Threshold    3", 80, 80, 300, 40, 120, 120, 120);
    musicText = Text("Toggle Music   ON", 80, 115, 300, 40, 120, 120, 120);
    sfxText = Text("Toggle Sounds    ON", 80, 150, 300, 40, 120, 120, 120);
    startText = Text("Begin Match", 80, 185, 300, 40, 120, 120, 120);

    //initialize variables
    loadSuccess = true;
    select = 0;
    selectCooldown = 0;
    humans = 2;
    computers = 0;
    winThresh = 3;
    music = true;
    sfx = true;
}

void SetUp::events()
{
    //update eventhandler
    eventhandler.update();
    
    //update timer
    timer.update();
    
    //update selection cooldown
    if (selectCooldown > 0)
        selectCooldown -= timer.getDelta();
    
    //user closes the window
    if (eventhandler.windowClosed())
        nextState = STATE_EXIT;
    
    //controller input
    for (int i = 0; i < 4; i++)
    {
        //make selection (start game or quit)
        if ((eventhandler.buttonTapped(START_BUTTON, i)) ||
            (eventhandler.buttonTapped(X_BUTTON, i)))
        {
            switch (select)
            {
                case 0:
                    humans++;
                    if (humans > 4)
                    {
                        humans = 1;
                    }
                    if (humans + computers > 4)
                    {
                        computers = 0;
                    }
                    break;
                
                case 1:
                    if (humans + computers < 4)
                    {
                        computers++;
                        if (computers > 3)
                        {
                            humans = 0;
                        }
                    } else {
                        computers = 0;
                    }
                    break;
                
                case 2:
                    winThresh++;
                    if (winThresh > 5)
                    {
                        winThresh = 3;
                    }
                    break;
                    
                case 3:
                    music = !music;
                    break;
                
                case 4:
                    sfx = !sfx;
                    break;
                    
                default:
                case 5:
                    nextState = STATE_BATTLE;
                    break;
            }
        }
        
        //change selection
        if (eventhandler.getYAxisLeft(i) < 0)
        {
            if (selectCooldown <= 0)
            {
                select--;
                if (select < 0)
                    select = 5;
                selectCooldown = .2;
            }
        }
        else if (eventhandler.getYAxisLeft(i) > 0)
        {
            if (selectCooldown <= 0)
            {
                select++;
                if (select > 5)
                    select = 0;
                selectCooldown = .2;
            }
        }
    }
}

void SetUp::logic()
{
    //update humans count
    switch(humans)
    {
        default:
        case 1:
            humansText.setValue("Human   Players    1");
            break;
        case 2:
            humansText.setValue("Human   Players    2");
            break;
        case 3:
            humansText.setValue("Human   Players    3");
            break;
        case 4:
            humansText.setValue("Human   Players    4");
            break;
    }
    
    //update computers count
    switch(computers)
    {
        default:
        case 0:
            computersText.setValue("Computer   Players    0");
            break;
        case 1:
            computersText.setValue("Computer   Players    1");
            break;
        case 2:
            computersText.setValue("Computer   Players    2");
            break;
        case 3:
            computersText.setValue("Computer   Players    3");
            break;
    }
    
    //update win threshold count
    switch(winThresh)
    {
        default:
        case 3:
            winThreshText.setValue("Win Threshold    3");
            break;
        case 4:
            winThreshText.setValue("Win Threshold    4");
            break;
        case 5:
            winThreshText.setValue("Win Threshold    5");
            break;
    }
    
    //update music toggle
    if (music)
    {
        musicText.setValue("Toggle Music   ON");
    } else {
        musicText.setValue("Toggle Music   OFF");
    }
    
    //update sfx toggle
    if (sfx)
    {
        sfxText.setValue("Toggle Sounds   ON");
    } else {
        sfxText.setValue("Toggle Sounds   OFF");
    }
    
    //selection highlighting
    switch (select)
    {
        default: //# of human players
        case 0:
            humansText.setCol(173, 67, 67);
            computersText.setCol(120, 120, 120);
            winThreshText.setCol(120, 120, 120);
            musicText.setCol(120, 120, 120);
            sfxText.setCol(120, 120, 120);
            startText.setCol(120, 120, 120);
            break;
            
        case 1: //# of computer players
            humansText.setCol(120, 120, 120);
            computersText.setCol(173, 67, 67);
            winThreshText.setCol(120, 120, 120);
            musicText.setCol(120, 120, 120);
            sfxText.setCol(120, 120, 120);
            startText.setCol(120, 120, 120);
            break;
            
        case 2: //win threshold
            humansText.setCol(120, 120, 120);
            computersText.setCol(120, 120, 120);
            winThreshText.setCol(173, 67, 67);
            musicText.setCol(120, 120, 120);
            sfxText.setCol(120, 120, 120);
            startText.setCol(120, 120, 120);
            break;
            
        case 3: //toggle music
            humansText.setCol(120, 120, 120);
            computersText.setCol(120, 120, 120);
            winThreshText.setCol(120, 120, 120);
            musicText.setCol(173, 67, 67);
            sfxText.setCol(120, 120, 120);
            startText.setCol(120, 120, 120);
            break;
            
        case 4: //toggle sfx
            humansText.setCol(120, 120, 120);
            computersText.setCol(120, 120, 120);
            winThreshText.setCol(120, 120, 120);
            musicText.setCol(120, 120, 120);
            sfxText.setCol(173, 67, 67);
            startText.setCol(120, 120, 120);
            break;
            
        case 5: //start game
            humansText.setCol(120, 120, 120);
            computersText.setCol(120, 120, 120);
            winThreshText.setCol(120, 120, 120);
            musicText.setCol(120, 120, 120);
            sfxText.setCol(120, 120, 120);
            startText.setCol(173, 67, 67);
            break;
    }
}

void SetUp::render()
{
    //clear
    window->clear();
    
    //draw text
    window->draw(&humansText);
    window->draw(&computersText);
    window->draw(&winThreshText);
    window->draw(&musicText);
    window->draw(&sfxText);
    window->draw(&startText);
    
    //render everything
    window->render();
}
//title.cpp

#include "header/title.hpp"

Title::Title()
{
    //initialize graphics
    logo = Graphic(0, 50, 20, 375, 120, 0, 1932, 853, 220, SHEET_TITLE);
    blackhole = Graphic(0, 180, 30, 100, 100, 195, 0, 433, 370, SHEET_TITLE);
    
    //initialize text
    start = Text("Start Game",  185, 150, 80, 35, 86, 250, 240);
    quit = Text("Quit",         185, 180, 80, 35, 120, 120, 120);
    
    //initialize variables
    loadSuccess = true;
    select = 0;
    selectCooldown = 0;
}

void Title::events()
{
    //update event handler
    eventhandler.update();
    
    //update timer
    timer.update();
    
    //update selection cooldown
    if (selectCooldown > 0)
        selectCooldown -= timer.getDelta();
    
    //user closes window
    if (eventhandler.windowClosed())
        nextState = STATE_EXIT;
    
    //controller input
    for (int i = 0; i < 4; i++)
    {
        //make selection (start game or quit)
        if ((eventhandler.buttonTapped(START_BUTTON, i)) ||
            (eventhandler.buttonTapped(X_BUTTON, i)))
        {
            if (select == 0)
            {
                nextState = STATE_SETUP;
            } else {
                nextState = STATE_EXIT;
            }
        }
        
        //change selection
        if (eventhandler.getYAxisLeft(i) != 0)
        {
            if (selectCooldown <= 0)
            {
                if (select == 0)
                {
                    select = 1;
                } else {
                    select = 0;
                }
                selectCooldown = .3;
            }
        }
    }
}

void Title::logic()
{
    //selection highlighting
    if (select == 0)
    {
        start.setPos(180, 145, 90, 45);
        start.setCol(173, 67, 67);
        
        quit.setPos(185, 180, 80, 35);
        quit.setCol(120, 120, 120);
    } else {
        start.setPos(185, 150, 80, 35);
        start.setCol(120, 120, 120);
        
        quit.setPos(180, 175, 90, 45);
        quit.setCol(173, 67, 67);
    }
}

void Title::render()
{
    //clear
    window->clear();
    
    //draw graphics
    window->draw(blackhole.getFrame());
    window->draw(logo.getFrame());
    
    //draw text
    window->draw(&start);
    window->draw(&quit);
    
    //render everything
    window->render();
}


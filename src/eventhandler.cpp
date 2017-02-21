//eventhandler.cpp

#include "header/eventhandler.hpp"

EventHandler::EventHandler()
{
    //initialize variables
    quit = false;
    for (int i = 0; i < 20; i++)
    {
        keys[i] = -1;
        time[i] = 0;
    }
    for (int i = 0; i < 5; i++)
        taps[i] = 0;
    
    //game controller intialization
    if( SDL_NumJoysticks() < 1 )
    {
        printf( "Warning: No joysticks connected!\n" );
    }
    else
    {
        //Load joysticks
        for (int i = 0; i < 4; i++)
        {
            controller[i] = NULL;
            controller[i] = SDL_JoystickOpen(i);
            if( controller[i] == NULL )
            {
                printf( "Warning: Couldn't open controller! SDL Error: %s\n", SDL_GetError() );
            }
        }
    }
}

EventHandler::~EventHandler()
{
    //close game controllers
    for (int i = 0; i < 4; i++)
    {
        SDL_JoystickClose(controller[i]);
        controller[i] = NULL;
    }
}

void EventHandler::update()
{
    timer.update();
    
    while (SDL_PollEvent (&event) )
    {
        //user hits a key
        if (event.type == SDL_KEYDOWN)
            press(event.key.keysym.sym);
        
        //user releases a key
        if (event.type == SDL_KEYUP)
            release(event.key.keysym.sym);
        
        //user hits controller button
        if (event.type == SDL_JOYBUTTONDOWN)
        {
            //for each player...
            for (int i = 0; i < 4; i++)
            {
                if (event.jbutton.which == i)
                {
                    //which button was hit?
                    switch((int)event.jbutton.button)
                    {
                        case 3: //start button
                            press(START_BUTTON + i);
                            break;
                        case 12: //triangle button
                            press(T_BUTTON + i);
                            break;
                        case 13: //o button
                            press(O_BUTTON + i);
                            break;
                        case 14: //x button
                            press(X_BUTTON + i);
                            break;
                        case 15: //square button
                            press(S_BUTTON + i);
                            break;
                        case 10: //left bumper button
                            press(L1_BUTTON + i);
                            break;
                        case 8: //left trigger button
                            press(L2_BUTTON + i);
                            break;
                        case 11: //right bumper button
                            press(R1_BUTTON + i);
                            break;
                        case 9: //right trigger button
                            press(R2_BUTTON + i);
                            break;
                    }
                }
            }
        }
        
        //user releases controller button
        if (event.type == SDL_JOYBUTTONUP)
        {
            //for each player...
            for (int i = 0; i < 4; i++)
            {
                if (event.jbutton.which == i)
                {
                    //which button was hit?
                    switch((int)event.jbutton.button)
                    {
                        case 3: //start button
                            release(START_BUTTON + i);
                            break;
                        case 12: //triangle button
                            release(T_BUTTON + i);
                            break;
                        case 13: //o button
                            release(O_BUTTON + i);
                            break;
                        case 14: //x button
                            release(X_BUTTON + i);
                            break;
                        case 15: //square button
                            release(S_BUTTON + i);
                            break;
                        case 10: //left bumper button
                            release(L1_BUTTON + i);
                            break;
                        case 8: //left trigger button
                            release(L2_BUTTON + i);
                            break;
                        case 11: //right bumper button
                            release(R1_BUTTON + i);
                            break;
                        case 9: //right trigger button
                            release(R2_BUTTON + i);
                            break;
                    }
                }
            }
        }
        
        //user changes controller joystick position
        if (event.type == SDL_JOYAXISMOTION)
        {
            //for each player...
            for (int i = 0; i < 4; i++)
            {
                if (event.jaxis.which == i)
                {
                    //update stored value
                    switch(event.jaxis.axis)
                    {
                    case 0: //left x-axis
                        //if the value is outside of dead zone...
                        if ((event.jaxis.value < -JOYSTICK_DEAD_ZONE)
                            || (event.jaxis.value > JOYSTICK_DEAD_ZONE))
                        {
                            //get value and reduce to 0-100
                            leftAxis[i].setX(event.jaxis.value*(100.0/32767.0));
                        } else {
                            leftAxis[i].setX(0);
                        }
                        break;
                    
                    case 1: //left y-axis
                        //if the value is outside of dead zone...
                        if ((event.jaxis.value < -JOYSTICK_DEAD_ZONE)
                            || (event.jaxis.value > JOYSTICK_DEAD_ZONE))
                        {
                            //get value and reduce to 0-100
                            leftAxis[i].setY(event.jaxis.value*(100.0/32767.0));
                        } else {
                            leftAxis[i].setY(0);
                        }
                        break;
                        
                    //TODO: right x-axis
                    //TODO: right y-axis
                    }
                    
                    //TODO: map value from square to circle
                    //leftAxis[i].mapToCircle();
                }
            }
        }
        
        //user requests quit
        if (event.type == SDL_QUIT)
            quit = true;
    }
}

bool EventHandler::windowClosed()
{
    return quit;
}

bool EventHandler::keyHeld(int k, int t)
{
    for (int i = 0; i < 20; i++)
        if ((k == keys[i]) && (timer.getTime()-time[i] > t))
            return true;
    
    return false;
}

bool EventHandler::keyTapped(int k)
{
    for (int i = 0; i < 5; i++)
        if (k == taps[i])
        {
            taps[i] = 0;
            return true; //yes it's pressed
        }
    return false; //no it's not pressed
}

bool EventHandler::buttonHeld(int b, int p, int t)
{
    for (int i = 0; i < 20; i++)
        if ((b+p == keys[i]) && (timer.getTime()-time[i] > t))
            return true;
    
    return false;
}

bool EventHandler::buttonTapped(int b, int p)
{
    for (int i = 0; i < 5; i++)
        if (b+p == taps[i])
        {
            taps[i] = 0;
            return true; //yes it's pressed
        }
    
    return false; //no it's not pressed
}

float EventHandler::getXAxisLeft(int player)
{
    if ((player >= 0) && (player <= 4))
        return leftAxis[player].getX();
    else return 0;
}

float EventHandler::getYAxisLeft(int player)
{
    if ((player >= 0) && (player <= 4))
        return leftAxis[player].getY();
    else return 0;
}


void EventHandler::press(int k)
{
    //is it in there?
    for (int i = 0; i < 20; i++)
        if (keys[i] == k)
            return;
    //fill it in if it's not there
    for (int i = 0; i < 20; i++)
        if (keys[i] == -1)
        {
            keys[i] = k;
            time[i] = timer.getTime();
            return;
        }
}

void EventHandler::release(int k)
{
    for (int i = 0; i < 20; i++)
        if (keys[i] == k)
        {
            //release the key
            keys[i] = -1;
            //was it held for a short time?
            if (timer.getTime()-time[i] < TAP_TIME)
            {
                for (int i = 0; i < 4; i++)
                    taps[i+1] = taps[i];
                taps[0] = k;
            }
        }
}

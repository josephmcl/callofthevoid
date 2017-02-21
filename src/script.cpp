//frame.cpp

#include "header/script.hpp"

Script::Script(string path)
{
    //initialize variables
    move = -1;
    dir = -1;
    l = 0;
    frame = new Frame(0, 0, 0, 0, 0, 0, 0, 0, 0, SHEET_KNIGHT);

    //open stream
    ifstream read;                  //create ifstream object
    read.open(path, ios::in);       //open the file
    string s;                       //string for recording each new line
    
    //read to vector
    if (read.is_open())     //check to make sure it's open...
    {
        while (getline(read, s)) //for each line...
        {
            lines.push_back(s);
        }
    } else {
        cout << "Warning: Couldn't open path " << path << endl;
    }
    
    //close stream
    read.close();
}

bool Script::done()
{
    return l > lines.size();
}

void Script::next()
{
    //initialize variables
    move = -1;
    dir = -1;

    //if this is a valid line...
    if (l < lines.size())
    {
        //...break line into commands...
        vector <string> commands = split(lines[l], ' ');
    
        //...and execute them to create a new frame
        frame = new Frame(0, 0, 0, 0, 0, 0, 0, 0, 0, SHEET_KNIGHT);
        
        for (int j = 0; j < commands.size(); j++)
        {
            //move commands (no arguments)
            if (commands[j] == "IDLE")
            {
                move = MOVE_NONE;
            } else if (commands[j] == "WALK")
            {
                move = MOVE_WALK;
            } else if (commands[j] == "LIGHT")
            {
                move = MOVE_LIGHT_ATTACK;
            } else if (commands[j] == "ROLL")
            {
                move = MOVE_ROLL;
            } else if (commands[j] == "BLOCK")
            {
                move = MOVE_BLOCK;
            } else if (commands[j] == "STUN")
            {
                move = MOVE_STUN;
            } else if (commands[j] == "PRONE")
            {
                move = MOVE_PRONE;
            }
            //direction commands (no arguments)
            else if (commands[j] == "SW")
            {
                dir = SOUTHWEST;
            } else if (commands[j] == "SE")
            {
                dir = SOUTHEAST;
            } else if (commands[j] == "E")
            {
                dir = EAST;
            } else if (commands[j] == "NE")
            {
                dir = NORTHEAST;
            } else if (commands[j] == "NW")
            {
                dir = NORTHWEST;
            } else if (commands[j] == "W")
            {
                dir = WEST;
            }
            
            //SDL_Rect commands (4 integer arguments each for x, y, w, h)
            else if (commands[j] == "POS")
            {
                if (j + 4 < commands.size())
                {
                    SDL_Rect foo = rect(stoi(commands[j+1]), stoi(commands[j+2]),
                                    stoi(commands[j+3]), stoi(commands[j+4]));
                    frame->setPos(foo);
                    j += 4;
                }
            } else if (commands[j] == "CROP")
            {
                if (j + 4 < commands.size())
                {
                    SDL_Rect foo = rect(stoi(commands[j+1]), stoi(commands[j+2]),
                                    stoi(commands[j+3]), stoi(commands[j+4]));
                    frame->setCrop(foo);
                    j += 4;
                }
            } else if (commands[j] == "HITBOX")
            {
                if (j + 4 < commands.size())
                {
                    frame->addHitBox(
                        stoi(commands[j+1])-frame->getX(),
                        stoi(commands[j+2])-frame->getY(),
                        stoi(commands[j+3]), stoi(commands[j+4]));
                    j += 4;
                }
            } else if (commands[j] == "PUNISHBOX")
            {
                if (j + 4 < commands.size())
                {
                    frame->addPunishBox(
                        stoi(commands[j+1])-frame->getX(),
                        stoi(commands[j+2])-frame->getY(),
                        stoi(commands[j+3]), stoi(commands[j+4]));
                    j += 4;
                }
            } else if (commands[j] == "STANDBOX")
            {
                if (j + 4 < commands.size())
                {
                    frame->addStandBox(
                        stoi(commands[j+1])-frame->getX(),
                        stoi(commands[j+2])-frame->getY(),
                        stoi(commands[j+3]), stoi(commands[j+4]));
                    j += 4;
                }
            }
        }
    }
    
    l++; //increment line number
}

int Script::getMove()
{
    return move;
}

int Script::getDir()
{
    return dir;
}

Frame* Script::getFrame()
{
    return frame;
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    std::vector<string> elems;
    split(s, delim, elems);
    return elems;
}
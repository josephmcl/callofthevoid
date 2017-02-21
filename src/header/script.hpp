//script.hpp

#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "utility.hpp"
#include "frame.hpp"

using namespace std;

class Script
//opens files and reads scripts from them
{
public:
    //constructors
    Script(){}
    Script(string path);    //opens the file stream and makes sure everything's a-ok
    
    //getters
    bool done();            //checks if we're done. if not, updates move/dir and frame
    void next();            //goes to the next frame
    int getMove();          //gets current move
    int getDir();           //gets current dir
    Frame* getFrame();      //gets current frame
    
private:
    int move;                   //current move
    int dir;                    //current direction
    Frame* frame;               //current frame
    int l;                      //which line are we on?
    vector <string> lines;      //all parsed frames
};

vector<string> &split(const string &s, char delim, vector<string> &elems);

vector<string> split(const string &s, char delim);

#endif
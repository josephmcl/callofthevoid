//audiohandler.hpp

#ifndef _AUDIOHANDLER_H
#define _AUDIOHANDLER_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class AudioHandler
{
public:
    //constructors and deconstructors
    AudioHandler();
    ~AudioHandler();
    
    //methods
    //void loadMusic();                             //loads a music file
    void loadSample(string path, string name);      //loads a sample file
    void update();                                  //keep music/sfx going
    //void toggleMusic();                           //toggle music on and off
    //void toggleSamples();                         //toggle samples on and off
    //bool getSuccess();                            //did this successfully load?
    void playSample(string s);                      //plays a sample

private:
    bool success;
    bool musicMuted;
    bool samplesMuted;
    int currentMusic;
    
    //SDL
    Mix_Music* music;
    vector <string> sampleNames;
    vector <Mix_Chunk*> samples;
};

#endif

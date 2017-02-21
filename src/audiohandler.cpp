//audiohandler.cpp

#include "header/audiohandler.hpp"
#include <iostream>

AudioHandler::AudioHandler()
{
    success = true;
    musicMuted = true;
    samplesMuted = false;
}

AudioHandler::~AudioHandler()
{
    
    //free all music objects
    Mix_FreeMusic(music);
    
    //free all sample (chunk) objects
    for (int i = 0; i < samples.size(); i++)
        Mix_FreeChunk(samples.at(i));
}

void AudioHandler::loadSample(string path, string name)
{
    samples.push_back(Mix_LoadWAV(path.c_str()));
    if (samples.back() == NULL)
    {
        cout << "Warning: failed to load sample at path " << path << endl;
        Mix_FreeChunk(samples.back());
        samples.pop_back();
        success = false;
    } else {
        sampleNames.push_back(name);
    }
}

void AudioHandler::update()
{
    if (Mix_PlayingMusic() == 0)
    {
        if (!musicMuted)
        {
            Mix_PlayMusic(music, -1);
        }
    } else {
        if (Mix_PausedMusic() == 1)
        {
            if (!musicMuted)
            {
                Mix_ResumeMusic();
            }
        }
        else
        {
            if (musicMuted)
            {
                Mix_PauseMusic();
            }
        }
    }
}

void AudioHandler::playSample(string s)
{
    for (int i = 0; i < sampleNames.size(); i++)
    {
        if ((sampleNames.at(i) == s) && (samples.size() > i))
        {
            Mix_PlayChannel(0, samples.at(i), 0);
        }
    }
}
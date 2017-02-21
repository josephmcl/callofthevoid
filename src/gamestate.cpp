//gamestate.cpp

#include "header/gamestate.hpp"

bool GameState::getLoadSuccess() { return loadSuccess; }

int GameState::getNextState() { return nextState; }

void GameState::setWindow(Window* w) { window = w; }

int GameState::getHumans() { return humans; }

int GameState::getComputers() { return computers; }

int GameState::getWinThresh() { return winThresh; }

bool GameState::getMusic() { return music; }

bool GameState::getSFX() { return sfx; }
//maphandler.hpp

#ifndef _MAPHANDLER_H
#define _MAPHANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "graphic.hpp"
#include "terrain.hpp"

using namespace std;

class MapHandler
{
public:
    //constructor
    MapHandler();
 
    //public methods
    bool loadMap(string path);  //loads a map script from the specified relative path (text files only)
    int getXTile();
    int getYTile();
    int getXTer();
    int getYTer();
    Graphic getNextTile();      //returns the next tile (order: left to right, top to bottom)
    Terrain getNextTerrain();   //returns the next piece of terrain (walls, trees, rocks, etc.)
    
private:
    //members
    char map[30][14];           //the currently loaded map script (a string read from a text file)
    int xTile, yTile;           //where are we in our crawl through the map file with (respect to tiles)?
    int xTer, yTer;             //where are we in our crawl through the map file with (respect to terrain)?
    
    Graphic tile;               //last generated tile
    Terrain terrain;            //last generated terrain
};

#endif

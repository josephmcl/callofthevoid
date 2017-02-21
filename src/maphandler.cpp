//maphandler.cpp

#include "header/maphandler.hpp"

MapHandler::MapHandler()
{
    xTer = 0;
    yTer = 0;
    xTile = 0;
    yTile = 0;
}

bool MapHandler::loadMap(string path)
{
    ifstream read;                  //create ifstream object
    read.open(path, ios::in);       //open the file
    string line;
    int x = 0;
    int y = 0;
    
    if (read.is_open())
    {
        while (getline(read, line)) //for each line...
        {
            //if we've run out of y space, stop looping
            if (y >= 14)
                break;
            
            //read characters from line to file
            x = 0;
            for (x = 0; x < line.size(); x++)
            {
                //if we're run out of x space, stop looping
                if (x >= 30)
                    break;
                
                //place the character on our map
                map[x][y] = line.at(x);
            }
            
            //increment y position
            y++;
        }
    } else {
        cout << "Warning: couldn't read map file!" << endl;
        return false; //couldn't load file
    }
    
    //close the file stream
    read.close();

    //report that we successfully read the map
    return true;
}

int MapHandler::getXTer() { return xTer; }

int MapHandler::getYTer() { return yTer; }

int MapHandler::getXTile() { return xTile; }

int MapHandler::getYTile() { return yTile; }

Graphic MapHandler::getNextTile()
{
    //find the appropriate tile graphic and store it
    Graphic temp = Graphic();
    switch(map[xTile][yTile])
    {
        //grass tile
        case '.':
        case 'T':
            if ((rand() % 20) > 0)
            {
                temp = Graphic(0, xTile*TILES_X, yTile*TILES_Y+UI_HEIGHT, 16, 16, 0, 0, 16, 16, SHEET_TILES);
            } else {
                temp = Graphic(0, xTile*TILES_X, yTile*TILES_Y+UI_HEIGHT, 16, 16, 16, 0, 16, 16, SHEET_TILES);
            }
            break;
    }
    
    //increment x/y counters
    xTile++;
    if (xTile >= 30)
    {
        xTile = 0;
        yTile++;
    }
    
    return temp;
}

Terrain MapHandler::getNextTerrain()
{
    //find the appropriate tile graphic and store it
    Terrain temp = Terrain();
    Frame frame;
    switch(map[xTer][yTer])
    {
        //trees (picks from a selection of trees)
        case 'T':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 32, 64, 0, 0, 32, 64, SHEET_TERRAIN);
            frame.addStandBox(5, 40, 22, 20);
            temp.addFrame(frame);
            break;
            
        case '0':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 128, 0, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '1':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 144, 0, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '2':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 160, 0, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '3':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 176, 0, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '4':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 128, 16, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '5':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 144, 16, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '6':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 160, 16, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '7':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 176, 16, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
            
        case '8':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 128, 32, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case '9':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 144, 32, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'A':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 160, 32, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'B':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 176, 32, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'C':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 128, 48, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'D':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 144, 48, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'E':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 160, 48, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
        
        case 'F':
            frame = Frame(0, xTer*TILES_X, yTer*TILES_Y+UI_HEIGHT, 16, 16, 176, 48, 16, 16, SHEET_TERRAIN);
            frame.addStandBox(0, 0, 16, 16);
            temp.addFrame(frame);
            break;
    }
    
    //increment x/y counters
    xTer++;
    if (xTer >= 30)
    {
        xTer = 0;
        yTer++;
    }
    
    return temp;
}
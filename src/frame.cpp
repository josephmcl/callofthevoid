//frame.cpp

#include "header/frame.hpp"

Frame::Frame(int delayTime, int pos_x, int pos_y, int pos_width, int pos_height,
        int crop_x, int crop_y, int crop_width, int crop_height, int sheet_id)
{
    pos.x = pos_x;
    pos.y = pos_y;
    delay = delayTime;
    pos.w = pos_width;
    pos.h = pos_height;
    crop.x = crop_x;
    crop.y = crop_y;
    crop.w = crop_width;
    crop.h = crop_height;
    sheet = sheet_id;
}

int Frame::getX() { return pos.x; }

int Frame::getY() { return pos.y; }

int Frame::getW() { return pos.w; }

int Frame::getH() { return pos.h; }

int Frame::getSheet() { return sheet; }

SDL_Rect Frame::getPos() { return pos; }

SDL_Rect Frame::getCrop() { return crop; }

RectList* Frame::getHitBox()
//returns a pointer to this fighter's list of hit boxes
{
    return &hit;
}

RectList* Frame::getPunishBox()
{
    return &punish;
}

RectList* Frame::getStandBox()
{
    return &stand;
}

int Frame::getStandY()
{
    if (stand.getSize() > 0)
        return stand.getRect(0).y + stand.getRect(0).h;
    return 0;
}

void Frame::addHitBox(int x, int y, int w, int h)
{
    hit.addRect(x, y, w, h);
}

void Frame::addPunishBox(int x, int y, int w, int h)
{
    punish.addRect(x, y, w, h);
}

void Frame::addStandBox(int x, int y, int w, int h)
{
    stand.addRect(x, y, w, h);
}

void Frame::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}

void Frame::setPos(int x, int y, int w, int h)
{
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
}

void Frame::setPos(SDL_Rect p)
{
    pos = p;
}

void Frame::setX(int x)
{
    pos.x = x;
}

void Frame::setY(int y)
{
    pos.y = y;
}

void Frame::setCrop(SDL_Rect c)
{
    crop = c;
}

bool Frame::collides(Frame* f, short int collisionType)
{
    //variables
    SDL_Rect rect1;
    SDL_Rect rect2;

    switch(collisionType)
    {
    case STAND:
        //compare all stand boxes for both frames
        for (int i = 0; i < stand.getSize(); i++)
        for (int j = 0; j < f->getStandBox()->getSize(); j++)
        {
            //retrieve the relevant stand boxes
            rect1 = stand.getRect(i);
            rect2 = f->getStandBox()->getRect(j);
            
            //update rectangle position relative to frame
            rect1.x += pos.x;
            rect1.y += pos.y;
            rect2.x += f->getX();
            rect2.y += f->getY();
            
            //check for collision
            if ((rect1.x < rect2.x + rect2.w) &&
                (rect1.x + rect1.w > rect2.x) &&
                (rect1.y < rect2.y + rect2.h) &&
                (rect1.h + rect1.y > rect2.y))
                    return true; //collision detected!
        }
        break;
        
    case HIT:
        //compare all hit boxes to all punish boxes for both frames
        for (int i = 0; i < hit.getSize(); i++)
        for (int j = 0; j < f->getPunishBox()->getSize(); j++)
        {
            //retrieve the relevant hit/punish boxes
            rect1 = hit.getRect(i);
            rect2 = f->getPunishBox()->getRect(j);
            
            //update rectangle position relative to frame
            rect1.x += pos.x;
            rect1.y += pos.y;
            rect2.x += f->getX();
            rect2.y += f->getY();
            
            //check for collision
            if ((rect1.x < rect2.x + rect2.w) &&
                (rect1.x + rect1.w > rect2.x) &&
                (rect1.y < rect2.y + rect2.h) &&
                (rect1.h + rect1.y > rect2.y))
                    return true; //collision detected!
        }
        break;
    }
    
    return false; //no collision
}
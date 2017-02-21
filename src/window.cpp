//window.cpp

#include "header/constants.hpp"
#include "header/window.hpp"

Window::Window()
{
    loadSuccess = true;
    
    //initialize SDL objects
    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL)
    {
        cout << "Failed to create window: " << SDL_GetError() << endl;
        loadSuccess = false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        cout << "Renderer error: " << SDL_GetError() << endl;
        loadSuccess = false;
    }
    
    //load sprite sheets
    addTexture("assets/ui.png", SHEET_UI);
    addTexture("assets/title.png", SHEET_TITLE);
    addTexture("assets/tiles.png", SHEET_TILES);
    addTexture("assets/terrain.png", SHEET_TERRAIN);
    addTexture("assets/knight.png", SHEET_KNIGHT);
    
    //load fonts
    string path = "assets/ARCADECLASSIC.TTF";
    font = TTF_OpenFont(path.c_str(), 20);
    if (font == NULL)
    {
        cout << "Font load error." << endl;
        loadSuccess = false;
    }
}

Window::~Window()
{
    //clean up SDL
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    
    //destroy all textures
    for (int i = (int)texture.size(); i > 0; i--)
    {
        SDL_DestroyTexture(texture.back());
        texture.pop_back();
    }
    
    //destroy text utility surface & texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    
    //close fonts
    TTF_CloseFont(font);
    font = nullptr;
}

void Window::clear()
{
    //clear
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void Window::draw(Frame* frame)
{
    crop = frame->getCrop();
    pos = frame->getPos();
    
    //scale to pixel ratio
    pos = rect_mult(pos, PIXEL_RATIO);
    
    //if we have the correct sheet loaded, we draw the sprite
    int sheet = frame->getSheet();
    for (int i = 0; i < texture.size(); i++)
    {
        if (texture_id.at(i) == sheet)
            SDL_RenderCopy(renderer, texture.at(i), &crop, &pos);
    }
    
    //for debug: show hit/punish boxes
    if (SHOW_BOXES)
    {
        //show hit boxes
        RectList* rectlist = frame->getHitBox();
        for (int i = (int)rectlist->getSize()-1; i >= 0; i--)
        {
            crop = rect_mult(rectlist->getRect(i), PIXEL_RATIO);
            crop.x = crop.x + frame->getX() * PIXEL_RATIO;
            crop.y = crop.y + frame->getY() * PIXEL_RATIO;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderDrawRect(renderer, &crop);
        }
    
        //show punish boxes
        rectlist = frame->getPunishBox();
        for (int i = (int)rectlist->getSize()-1; i >= 0; i--)
        {
            crop = rect_mult(rectlist->getRect(i), PIXEL_RATIO);
            crop.x = crop.x + frame->getX() * PIXEL_RATIO;
            crop.y = crop.y + frame->getY() * PIXEL_RATIO;
            SDL_SetRenderDrawColor(renderer, 255, 50, 50, 0);
            SDL_RenderDrawRect(renderer, &crop);
        }
        
        //show stand boxes
        rectlist = frame->getStandBox();
        for (int i = (int)rectlist->getSize()-1; i >= 0; i--)
        {
            crop = rect_mult(rectlist->getRect(i), PIXEL_RATIO);
            crop.x = crop.x + frame->getX() * PIXEL_RATIO;
            crop.y = crop.y + frame->getY() * PIXEL_RATIO;
            SDL_SetRenderDrawColor(renderer, 50, 255, 50, 0);
            SDL_RenderDrawRect(renderer, &crop);
        }
    }
}

void Window::draw(Text* text)
{
    textSurface = TTF_RenderText_Solid
        (font, text->getValue().c_str(), text->getCol());
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect pos = rect_mult(text->getPos(), PIXEL_RATIO);
    SDL_RenderCopy(renderer, textTexture, NULL, &pos);
}

void Window::render()
{
    //render
    SDL_RenderPresent(renderer);
}

bool Window::getLoadSuccess() { return loadSuccess; }

void Window::addTexture(string path, int id)
{
    SDL_Texture* temp;
    texture.push_back(temp);
    texture_id.push_back(id);
    texture.back() = IMG_LoadTexture(renderer, path.c_str());
    if (texture.back() == NULL)
    {
        cout << "Image load error: " << IMG_GetError() << endl;
        loadSuccess = false;
    }
}

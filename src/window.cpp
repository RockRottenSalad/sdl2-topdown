
#include "window.hpp"

window::window(const char* winTitle, int w, int h)
    :gameWindow(NULL), renderer(NULL)
{
    gameWindow = SDL_CreateWindow(winTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    if(gameWindow == NULL)
        std::cout << "Win creation error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        std::cout << "Ren creation error: " << SDL_GetError() << std::endl;
}

window::~window()
{
    SDL_DestroyWindow(gameWindow);
    SDL_DestroyRenderer(renderer);
}

void window::clear()
{
    SDL_RenderClear(renderer);
}

void window::render(entity* objectArg, camera* playerCamera)
{
   SDL_Rect src = objectArg->getTextureSnippet();

   SDL_Rect dest;
   dest.x = objectArg->getPos().x - playerCamera->cameraPos.x;
   dest.y = objectArg->getPos().y - playerCamera->cameraPos.y;
   dest.w = src.w;
   dest.h = src.h;

   SDL_RenderCopyEx(renderer, objectArg->getTexture(), &src, &dest, objectArg->getAngle(), NULL, SDL_FLIP_NONE); 
}

void window::setViewPort(camera* playerCamera)
{
    SDL_Rect viewport;
    viewport.x = 0;
    viewport.y = 0;

    viewport.w = playerCamera->cameraPos.x;
    viewport.h = playerCamera->cameraPos.y;

    if(SDL_RenderSetScale(renderer, playerCamera->cameraPos.x, playerCamera->cameraPos.y) != 0)
        std::cout << "View port change error: " << SDL_GetError() << std::endl;
}

void window::present()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* window::loadTexture(const char* filePath)
{
    SDL_Texture* loadedTexture = NULL;
    loadedTexture = IMG_LoadTexture(renderer, filePath);
    
    if(loadedTexture == NULL)
        std::cout << "Texture not found: " << SDL_GetError() << std::endl;

    return loadedTexture;
}

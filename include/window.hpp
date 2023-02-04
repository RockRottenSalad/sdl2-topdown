#pragma once

#include<SDL2/SDL.h>
#include "object.hpp"

class window
{
    private:
        SDL_Window* gameWindow;
        SDL_Renderer* renderer;
    public:
        window(const char* winTitle, int w, int h);
        ~window();
        void clear();
        void render(entity* objectArg, camera* playerCamera);
        void setViewPort(camera* playerCamera);
        void present();
        SDL_Texture* loadTexture(const char* filePath);
};


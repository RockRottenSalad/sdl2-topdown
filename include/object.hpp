#pragma once

#include<SDL2/SDL.h>
#include<cmath>

#include "const.hpp"

struct vector2d
{
    float x, y;
    vector2d(float xArg, float yArg);
    vector2d();

    float angle(vector2d vecArg);
    vector2d diff(vector2d vecArg);
};

class entity
{
    private:
        vector2d pos;
        SDL_Texture* texture;
        SDL_Rect textureSnippet;
        float angle;
        vector2d accel = vector2d(0,0);
    public:
        entity(vector2d posArg, SDL_Texture* textureArg, SDL_Rect textureSnippetArg);
        entity();

        vector2d getPos();
        float getAngle();
        vector2d getAccel();
        SDL_Texture* getTexture();
        SDL_Rect getTextureSnippet();

        void changePos(vector2d posArg);
        void changeAngle(float angleArg);
        void changeAccel(vector2d accelArg);
        void changeTexture(SDL_Texture* textureArg);
        void changeTextureSnippet(SDL_Rect textureSnippetArg);

        void move(float dist);
};

struct camera
{
    vector2d cameraPos;

    void updateCamera(entity* plr);
};


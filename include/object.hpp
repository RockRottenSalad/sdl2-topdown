#pragma once

#include<SDL2/SDL.h>
#include<cmath>

#include "const.hpp"

struct vector2d
{
    float x, y;
    vector2d(float xArg, float yArg);
    vector2d();
    ~vector2d();

    float length();
    vector2d normalized();
    vector2d add(vector2d vecArg);
    vector2d scalar(float scalarArg);
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
        vector2d speed = vector2d(0,0);
        short hp;
        bool accelForward;
    public:
        entity(vector2d posArg, SDL_Texture* textureArg, SDL_Rect textureSnippetArg);
        entity();
        ~entity();

        vector2d getPos();
        float getAngle();
        vector2d getAccel();
        vector2d getSpeed();
        SDL_Texture* getTexture();
        SDL_Rect getTextureSnippet();
        short getHP();
        bool getAccelForward();

        void changePos(vector2d posArg);
        void changeAngle(float angleArg);
        void changeAccel(vector2d accelArg);
        void changeSpeed(vector2d speedArg);
        void changeTexture(SDL_Texture* textureArg);
        void changeTextureSnippet(SDL_Rect textureSnippetArg);
        void changeHP(short hpArg);
        void changeAccelForward(bool boolArg);

        void move(float dist);
        bool checkCollision(entity* objectArg);
};

struct camera
{
    vector2d cameraPos;

    void updateCamera(entity* plr);
};



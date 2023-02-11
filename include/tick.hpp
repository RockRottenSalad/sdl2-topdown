#pragma once

#include<SDL2/SDL.h>
#include<vector>
#include<iostream>

#include "window.hpp"
#include "const.hpp"
#include "controls.hpp"
#include "physics.hpp"

enum class gameState {PLAY, QUIT}; 

class game
{
    private:
        gameState _gameState;
        window* gameWindow = NULL;
        entity* playerEntity;
        camera* playerCamera;
        physics* physicsHandler;

        // renderlist = background, props etc
        std::vector<entity *> renderList;
        // ------------------- v
        std::vector<entity *> shipList;
        // bullets and such
        std::vector<entity *> projectileList;
        // used for copying/moving all pointers in vector
        std::vector<entity *> buffer;

        double fpsDelta = 0.0, tickDelta = 0.0;
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        int xMouse, yMouse;

    public:
        game(window* gameWindow, entity* plrArg);
        ~game();
        void eventHandler(SDL_Event event);
        void cleanUp();

        void addToRenderList(entity* objectArg);
        void addToProjectileList(entity* objectArg);
        void addToShipList(entity* objectArg);

        void drawRenderList();
        void deltaTick();
        void gameTick();
        void startGame();
        void gameLoop();
};


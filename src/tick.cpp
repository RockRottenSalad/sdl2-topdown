
#include "tick.hpp"
#include "controls.hpp"
#include<iostream>

game::game(window* windowArg, entity* plrArg)
    :gameWindow(windowArg), playerEntity(plrArg), playerCamera(new camera())
{
    SDL_Init(SDL_INIT_VIDEO);
}

game::~game()
{}

void game::eventHandler(SDL_Event event)
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            _gameState = gameState::QUIT;
            break;
        case SDL_KEYDOWN:
            handleKeyPress(event, playerEntity);
            break;
        case SDL_KEYUP:
            handleKeyLift(event, playerEntity);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handleMouseClick(playerEntity); 
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&xMouse, &yMouse);
            handleMouseMotion(xMouse, yMouse, playerEntity);
            break;
    }

}

void game::cleanUp()
{
    std::vector<entity *>::iterator i;
    for(i = renderList.begin(); i != renderList.end(); i++)
    {
        delete *i;
    }
}

void game::addToRenderList(entity* objectArg)
{
    game::renderList.push_back(objectArg);
}

void game::drawRenderList()
{
    std::vector<entity *>::iterator i;
    for(i = renderList.begin(); i != renderList.end(); i++)
    {
        gameWindow->render(*i, playerCamera);
    }
}

void game::deltaTick()
{
    last = now;
    now = SDL_GetPerformanceCounter();
    tickDelta += (float)(now - last)*1000 / (float)SDL_GetPerformanceFrequency();
    fpsDelta += (float)(now - last)*1000 / (float)SDL_GetPerformanceFrequency();
}

void game::gameTick()
{
    playerEntity->move(playerEntity->getAccel().y * tickDelta);
    playerCamera->updateCamera(playerEntity);
}

void game::startGame()
{
    _gameState = gameState::PLAY;
    game::gameLoop();
}

void game::gameLoop()
{
    SDL_Event event;

    while(_gameState == gameState::PLAY)
    {
        eventHandler(event);
        deltaTick();
        if(fpsDelta > TARGET_FPS)
        {
            gameWindow->clear();
            drawRenderList();
            gameWindow->present();

            fpsDelta = 0.0;
        }
        
        if(tickDelta > TICK_RATE)
        {
            gameTick();
            tickDelta = 0.0;
        }
    }
    delete gameWindow;
    delete playerCamera;
    cleanUp();
    SDL_Quit();
}


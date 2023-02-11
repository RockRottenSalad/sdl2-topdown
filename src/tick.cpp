
#include "tick.hpp"

game::game(window* windowArg, entity* plrArg)
    :gameWindow(windowArg), playerEntity(plrArg), playerCamera(new camera()), physicsHandler(new physics())
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
            addToProjectileList(handleMouseClick(playerEntity, gameWindow)); 
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&xMouse, &yMouse);
            handleMouseMotion(xMouse, yMouse, playerEntity);
            break;
    }

}

void game::cleanUp()
{
    delete gameWindow;
    delete playerCamera;

    std::vector<entity *>::iterator i;
    for(i = renderList.begin(); i != renderList.end(); i++)
    {
        delete *i;
    }

    for(i = projectileList.begin(); i != projectileList.end(); i++)
    {
        delete *i;
    }
}

void game::addToRenderList(entity* objectArg)
{
    renderList.push_back(objectArg);
}

void game::addToProjectileList(entity* objectArg)
{
    projectileList.push_back(objectArg);
}

void game::addToShipList(entity* objectArg)
{
    shipList.push_back(objectArg);
}

void game::drawRenderList()
{
    std::vector<entity *>::iterator i;
    for(i = renderList.begin(); i != renderList.end(); i++)
    {
        gameWindow->render(*i, playerCamera);
    }

    for(i = shipList.begin(); i != shipList.end(); i++)
    {
        gameWindow->render(*i, playerCamera);
    }

    for(i = projectileList.begin(); i != projectileList.end(); i++)
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
    // ALL OF THIS SPAGHETTI CODE NEEDS TO BE REFACTORED
    // |-> into the physics class
    if(playerEntity->getAccelForward() == true)
    {
        playerEntity->changeAccel(
            vector2d(
             ACCELERATION * cos(playerEntity->getAngle()*2 * M_PI / 180.0f),
             ACCELERATION * sin(playerEntity->getAngle()*2 * M_PI / 180.0f)) 
            );
            if(playerEntity->getSpeed().length() >= MAX_SPEED)
                playerEntity->changeSpeed(playerEntity->getSpeed().normalized().scalar(MAX_SPEED));
    }
    else
    {
        playerEntity->changeSpeed(playerEntity->getSpeed().scalar(INTERIA));
    }
    
    playerEntity->changeSpeed( playerEntity->getSpeed().add(playerEntity->getAccel()) );
    playerEntity->move(playerEntity->getSpeed().length());
    playerCamera->updateCamera(playerEntity);

    if(projectileList.empty())
        return;

    for(entity* itr : projectileList)
    {
        itr->move(itr->getAccel().y * tickDelta);
        itr->changeHP(itr->getHP() - 1);
        if(itr->checkCollision(renderList.back()))
        {
            std::cout << "hit" << std::endl;
        }
        if(itr->getHP() <= 0)
        {
            delete itr;
            continue;
        }
        buffer.push_back(itr);
    }

    projectileList.clear();

    for(entity* itr : buffer)
    {
        projectileList.push_back(itr);
    }

    buffer.clear();
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
    cleanUp();
    SDL_Quit();
}



#include "controls.hpp"

void handleKeyPress(SDL_Event event, entity* playerEntity)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_w:
            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, 0.5) );
            break;
        case SDLK_s:
            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, -0.2) );
            break;
        case SDLK_a:
            playerEntity->changeAccel(vector2d(0.2, playerEntity->getAccel().y) );
            break;
            
    }
}

void handleKeyLift(SDL_Event event, entity* playerEntity)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_w:
            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, 0) );
            break;
        case SDLK_s:
            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, 0) );
            break;
        case SDLK_a:
            playerEntity->changeAccel(vector2d(0.2, playerEntity->getAccel().y) );
            break;
    }
}

void handleMouseMotion(int xMouse, int yMouse, entity* playerEntity)
{
    playerEntity->changeAngle(vector2d(450,450).angle(vector2d( static_cast<float>(xMouse), static_cast<float>(yMouse) )) );
}

void handleMouseClick(entity* playerEntity)
{
    std::cout << "click" << std::endl; 
}

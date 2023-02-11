
#include "controls.hpp"

void handleKeyPress(SDL_Event event, entity* playerEntity)
{
    switch(event.key.keysym.sym)
    {
        case SDLK_w:
//            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, 0.5) );
            playerEntity->changeAccelForward(true);
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
//            playerEntity->changeAccel( vector2d(playerEntity->getAccel().x, 0) );
        //    playerEntity->changeAccel(vector2d(0,0));
            playerEntity->changeAccelForward(false);
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
    playerEntity->changeAngle(
            vector2d(WINDOW_RESOLUTION_X/2,WINDOW_RESOLUTION_Y/2).angle(vector2d(static_cast<float>(xMouse), static_cast<float>(yMouse) )) );
}

entity* handleMouseClick(entity* playerEntity, window* gameWindow)
{
    return createRegularBullet(playerEntity, gameWindow);
}

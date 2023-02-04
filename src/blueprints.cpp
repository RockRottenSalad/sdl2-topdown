
#include "blueprints.hpp"

entity* createRegularBullet(entity* playerEntity, window* gameWindow)
{
    SDL_Rect snip;
    snip.x = 0;
    snip.y = 0;
    snip.w = 5;
    snip.h = 20;

    vector2d pos(playerEntity->getPos().x + (playerEntity->getTextureSnippet().w/2), 
            playerEntity->getPos().y + playerEntity->getTextureSnippet().h/2);

    entity* projectile = new entity(pos, gameWindow->loadTexture("./res/gfx/bullet2.png"), snip);

    projectile->changeAngle(playerEntity->getAngle());
    projectile->changeAccel(vector2d(1, 1));
    projectile->changeHP((short)50);
    
    return projectile;
}


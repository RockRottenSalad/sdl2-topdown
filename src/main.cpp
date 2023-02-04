
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "window.hpp"
#include "object.hpp"
#include "tick.hpp"
#include "const.hpp"

int main(int argc, char ** argv)
{
    window *_window = new window("view", WINDOW_RESOLUTION_X, WINDOW_RESOLUTION_Y);

    SDL_Rect snip;
    snip.x = 0;
    snip.y = 0;
    snip.w = 64;
    snip.h = 64;

    entity* plr = new entity(vector2d(450,450), _window->loadTexture("./res/gfx/triangle.png"), snip);

    snip.w = 3840;
    snip.h = 2160;
    entity* background = new entity( vector2d(0, 0), _window->loadTexture("./res/gfx/background2.jpg"), snip);

    game gameInstance(_window, plr);
    gameInstance.addToRenderList(background);
    gameInstance.addToRenderList(plr);

    gameInstance.startGame();
    return 0;
}


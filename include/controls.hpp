#pragma once

#include<SDL2/SDL.h>
#include<iostream>

#include "object.hpp"
#include "blueprints.hpp"
#include "window.hpp"

void handleKeyPress(SDL_Event event, entity* playerEntity);
void handleKeyLift(SDL_Event event, entity* playerEntity);

void handleMouseMotion(int xMouse, int yMouse, entity* playerEntity);
entity* handleMouseClick(entity* playerEntity, window* gameWindow);


#pragma once

#include "game.hpp"
#include "window.hpp"

class physics
{
    private:
        window* gameWindow;
        game* gameInstance;
        std::vector<entity *> buffer;
        
    public:
        physics();
        void simulateAcceleration();
        void simulateInteria();
        void clearBuffer();
        void insertIntoBuffer();
        
};

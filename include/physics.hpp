#pragma once

#include<vector>

#include "object.hpp"

class physics
{
    private:
        std::vector<entity *> physicsBuffer;
    public:
        physics();
        ~physics();
        void simulateAcceleration();
        void simulateInteria();
        void clearBuffer();
        void insertIntoBuffer(entity* objectArg);
        
};


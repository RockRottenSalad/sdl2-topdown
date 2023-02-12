
#include "physics.hpp"

// Physics

physics::physics()
{}

physics::~physics()
{}


void physics::simulateAcceleration()
{
    for(entity* i : physicsBuffer)
    {
        if(i->getAccelForward())
        {
            i->changeAccel(
             vector2d(
             ACCELERATION * cos(i->getAngle()*2 * M_PI / 180.0f),
             ACCELERATION * sin(i->getAngle()*2 * M_PI / 180.0f)) 
            );
            i->changeSpeed(i->getSpeed().add(i->getAccel()));
        }
        i->move(i->getSpeed().length());
    }
}

void physics::simulateInteria()
{
    for(entity* i : physicsBuffer)
    {
        i->changeSpeed(i->getSpeed().scalar(INTERIA));
    }
}

void physics::clearBuffer()
{
    physicsBuffer.clear();
}

void physics::insertIntoBuffer(entity* objectArg)
{
    physicsBuffer.push_back(objectArg);
}

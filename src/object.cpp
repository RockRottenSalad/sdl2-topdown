
#include "object.hpp"

vector2d::vector2d(float xArg, float yArg)
    :x(xArg), y(yArg)
{}

vector2d::vector2d()
{}

vector2d::~vector2d()
{}

float vector2d::length()
{
    return sqrt(x*x + y*y);
}

vector2d vector2d::normalized()
{
    float lengthVal = this->length();
    return vector2d(x/lengthVal, y/lengthVal );
}

vector2d vector2d::add(vector2d vecArg)
{
    return vector2d(this->x + vecArg.x, this->y + vecArg.y);
}

vector2d vector2d::scalar(float scalarArg)
{
    return vector2d(x * scalarArg, y * scalarArg);
}

float vector2d::angle(vector2d vecArg)
{
    return (atan2(this->x - vecArg.x, this->y - vecArg.y) * (180.0/M_PI)) * -1.0;
}

vector2d vector2d::diff(vector2d vecArg)
{
    return vector2d( abs(this->x - vecArg.x), abs(this->y - vecArg.y) );
}

// ------------------------------------
entity::entity(vector2d posArg, SDL_Texture* textureArg, SDL_Rect textureSnippetArg)
    :pos(posArg), texture(textureArg), textureSnippet(textureSnippetArg), angle(0.0)
{

}

entity::entity()
{}

entity::~entity()
{}

// ENTITY GETTERS

vector2d entity::getPos()
{
    return pos;
}

float entity::getAngle()
{
    return angle;
}

vector2d entity::getAccel()
{
    return accel;
}

vector2d entity::getSpeed()
{
    return speed;
}

SDL_Texture* entity::getTexture()
{
    return texture;
}

SDL_Rect entity::getTextureSnippet()
{
    return textureSnippet;
}

short entity::getHP()
{
    return hp;
}

bool entity::getAccelForward()
{
    return accelForward;
}

// ENTITY SETTERS

void entity::changePos(vector2d posArg)
{
    pos = posArg;
}

void entity::changeAngle(float angleArg)
{
    angle = angleArg;
}

void entity::changeAccel(vector2d accelArg)
{
    accel = accelArg;
}

void entity::changeSpeed(vector2d speedArg)
{
    speed = speedArg;
}

void entity::changeTexture(SDL_Texture* textureArg)
{
    texture = textureArg;
}

void entity::changeTextureSnippet(SDL_Rect textureSnippetArg)
{
    textureSnippet = textureSnippetArg;
}

void entity::changeHP(short hpArg)
{
    hp = hpArg;
}

void entity::changeAccelForward(bool boolArg)
{
    accelForward = boolArg;
}

void entity::move(float dist)
{
    float rads = (angle - 90) * (M_PI / 180.0);
    vector2d curPos = pos;
    curPos.x += dist * cos(rads);
    curPos.y += dist * sin(rads);
    
    pos = curPos;
}

bool entity::checkCollision(entity* objectArg)
{
    if (    this->textureSnippet.y + objectArg->textureSnippet.h <= objectArg->textureSnippet.y 
        ||  this->textureSnippet.y >= objectArg->textureSnippet.y + objectArg->textureSnippet.h
        ||  this->textureSnippet.x + this->textureSnippet.w <= objectArg->textureSnippet.x
        ||  this->textureSnippet.x >= objectArg->textureSnippet.x + objectArg->textureSnippet.w
       )
    {
        return false;
    }

    return true;
}

// ------------------------------------

void camera::updateCamera(entity* plr)
{
    cameraPos.x = (plr->getPos().x + plr->getTextureSnippet().w / 2) - WINDOW_RESOLUTION_X / 2.0;
    cameraPos.y = (plr->getPos().y + plr->getTextureSnippet().h / 2) - WINDOW_RESOLUTION_Y / 2.0;
}


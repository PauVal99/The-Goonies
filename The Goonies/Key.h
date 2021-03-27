#pragma once
#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE

#include "Actor.h"

class Key : public Actor
{

public:

protected:
    virtual string setImage();
    virtual glm::vec2 setSize();
    virtual glm::vec2 setSizeInSpritesheet();
    virtual CollisionBox setCollisionBox();
    virtual void setAnimations() {}
    virtual void childUpdate(int deltaTime);

protected:


private:

};

#endif
#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Actor.h"

class Enemy: public Actor
{
public:
    virtual int damage() = 0;
    virtual void die() = 0;
    virtual bool isDead() = 0;
    virtual bool remove() = 0;

};

#endif
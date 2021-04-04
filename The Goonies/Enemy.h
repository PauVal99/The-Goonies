#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Actor.h"

class Enemy: public Actor
{
public:
    virtual int damage() = 0;
    virtual int experience() = 0;
    void die();
    bool isDead();

};

#endif
#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Actor.h"

class Enemy: public Actor
{
public:
    virtual int damage() = 0;

};

#endif
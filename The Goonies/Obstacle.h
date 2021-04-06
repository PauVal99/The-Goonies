#ifndef _OBSTACLE_INCLUDE
#define _OBSTACLE_INCLUDE

#include "Actor.h"

class Obstacle : public Actor
{
public:
	virtual int damage() = 0;
	virtual bool hit() = 0;
	
};

#endif
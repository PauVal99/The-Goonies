#ifndef _OBSTACLE_INCLUDE
#define _OBSTACLE_INCLUDE

#include "Actor.h"

class Obstacle : public Actor
{
public:
	virtual int damage() = 0;
	virtual int getType() = 0;
	virtual void changeAnimation(int animation) = 0;
	virtual bool isRestarting() = 0;
};

#endif
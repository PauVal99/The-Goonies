#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE

#include "Actor.h"

class PowerUp: public Actor
{
public:
	virtual void activatePowerUp() = 0;

	
};


#endif // _POWERUP_INCLUDE
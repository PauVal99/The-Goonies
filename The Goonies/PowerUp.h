#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE

#include "Actor.h"
#include "Player.h"

class PowerUp: public Actor
{
public:
	virtual void activatePowerUp(Player* player) = 0;

protected:
	glm::vec2 setSize();
	glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();

};


#endif // _POWERUP_INCLUDE
#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE

#include "Actor.h"
#include "Player.h"

class PowerUp: public Actor
{
public:
	virtual void activatePowerUp(Player* player) = 0;
	virtual bool activatable(Player* player) { return true; };
	bool isTaken();
	void take(Player* player);

protected:
	glm::vec2 setSize();
	glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
	void setAnimations();
	int setEndTime();
    int setEndAnimation();

};

#endif // _POWERUP_INCLUDE
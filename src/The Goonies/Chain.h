#ifndef _CHAIN_INCLUDE
#define _CHAIN_INCLUDE

#include "Actor.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Chain : public Actor
{
public:

protected:
	string setImage();
	glm::vec2 setSize();
	glm::vec2 setSizeInSpritesheet();
	CollisionBox setCollisionBox();

private:


private:

};

#endif // _PLAYER_INCLUDE
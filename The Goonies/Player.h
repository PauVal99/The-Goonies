#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Actor.h"
#include "CollisionBox.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Player: public Actor
{
	
protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheed();
    void setAnimations();
    void childUpdate();

private:
	void moveSideways();
	void climb();
	void jump();
	CollisionBox getCollisionBox();

private:
	bool jumping, climbing;
	int health, jumpAngle, startY;

};


#endif // _PLAYER_INCLUDE



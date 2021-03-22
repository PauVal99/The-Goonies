#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Actor.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Player: public Actor
{
public:
	void damage(const int &damage);

public:
	int health = 100;

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheed();
	CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate();

private:
	void moveSideways();
	void climb();
	void jump();

private:
	bool jumping = false, climbing = false, damaged = false;
	int jumpAngle, startY;

};


#endif // _PLAYER_INCLUDE



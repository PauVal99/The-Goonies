#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Actor.h"

#define HEALTH 100

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Player: public Actor
{
public:
	void takeDamage(const int &damage);
	void activateHyperShoes();
	void activateShield();
	void activateVitalityPotion();
	void activateExperiencePotion();

public:
	int health = 100;
	int experience = 0;

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
	CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);

private:
	void moveSideways();
	void climb();
	void jump();
	void wounded(int deltaTime);
	void getExperience();
	void incrementMaxVitality();

private:
	bool jumping = false, climbing = false, hasShield = false;
	int jumpAngle, startY, damageCooldown = 0,shieldCooldown=0, moveSpeed = 1, shieldHitsCounter = 0, maxVitality = 100, experienceIncrement = 20;

};


#endif // _PLAYER_INCLUDE



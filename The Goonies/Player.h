#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Actor.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

class Player: public Actor
{
public:
	void takeDamage(const int &damage);
	void addExperience(int exp);
	void activateHyperShoes();
	void activateShield();
	void activateVitalityPotion();
	void activateExperiencePotion();
	bool isTimePowerUpActivated();
	void activateTimePowerUp();
	void deactivateTimePowerUp();
	bool addKey();
	bool getHasKey();
	void removeKey();
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
	void incrementMaxHealth();

private:
	bool jumping = false, climbing = false, timePowerUp = false, hasKey = false;
	int  moveSpeed = 2, jumpAngle, startY;
	int experience = 0;
	int health = 100, maxHealth = 100;
	int damageCooldown = 0, shieldHitsCounter = 0;


};


#endif // _PLAYER_INCLUDE



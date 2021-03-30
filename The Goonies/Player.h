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
	void activateTimePowerUp();
	bool isTimePowerUpActive();
	void addKey();
	bool hasKey();
	void removeKey();
	bool isAttacking();
	CollisionBox getPunchCollisionBox();

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
	CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);

private:
	void attack(int deltaTime);
	void moveSideways();
	void climb();
	void jump();
	void wounded(int deltaTime);
	void timePowerUpUpdate(int deltaTime);
	void incrementMaxHealth();

private:
	bool jumping = false, climbing = false, timePowerUp = false, key = false;
	int  moveSpeed = 1, jumpAngle, startY;
	int experience = 0;
	int health = 100, maxHealth = 100;
	int damageCooldown = 0, timePoweUpCooldown = 0, shieldHitsCounter = 0, attacking = 0;

};

#endif // _PLAYER_INCLUDE
#include "PowerUp.h"
#include "SoundEngine.h"
#include "Key.h"
#define END_TIME 500

enum PowerUpAnims {
	IDLE, DISAPPEAR
};	

void PowerUp::setAnimations() {
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(IDLE, 4);
	sprite->addKeyframe(IDLE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(IDLE, glm::vec2(0.75f, 0.f));
	
	sprite->setAnimationSpeed(DISAPPEAR, 4);
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(DISAPPEAR, glm::vec2(0.5f, 0.f));

	sprite->changeAnimation(IDLE);
}

int PowerUp::setEndTime() {
	return END_TIME;
}

int PowerUp::setEndAnimation() {
	return DISAPPEAR;
}

glm::vec2 PowerUp::setSize() {
	return glm::vec2(16, 16);
}

glm::vec2 PowerUp::setSizeInSpritesheet() {
	return glm::vec2(0.25f, 1.f);
}

CollisionBox PowerUp::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = glm::ivec2(0, 0);
	collisionBox.max = setSize();
	return collisionBox;
}

bool PowerUp::isTaken() {
	return isEnded();
}

void PowerUp::playSound() {
	SoundEngine::getInstance()->playPickUpPowerUp();
}

void PowerUp::take(Player* player) {
	activatePowerUp(player);
	playSound();
	end();
}
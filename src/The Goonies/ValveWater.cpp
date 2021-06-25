#include <GL/glew.h>
#include <GL/glut.h>
#include "ValveWater.h"

#define COLLISION_BOX_MIN_CREATE_RIGHT glm::ivec2(0, 0)
#define COLLISION_BOX_MAX_CREATE_RIGHT glm::ivec2(16, 32)

#define COLLISION_BOX_MIN_FLUSH_RIGHT glm::ivec2(0, 0)
#define COLLISION_BOX_MAX_FLUSH_RIGHT glm::ivec2(32, 32)

#define COLLISION_BOX_MIN_CREATE_LEFT glm::ivec2(16, 0)
#define COLLISION_BOX_MAX_CREATE_LEFT glm::ivec2(32, 32)

#define COLLISION_BOX_MIN_FLUSH_LEFT glm::ivec2(0, 0)
#define COLLISION_BOX_MAX_FLUSH_LEFT glm::ivec2(32, 32)

#define DIE_TIME 0

enum ValveWaterAnims
{
	CREATE, FLUSH
};

string ValveWater::setImage() {
	return "images/Obstacles/ValveWater.png";
}

glm::vec2 ValveWater::setSize() {
	return glm::vec2(32, 32);
}

glm::vec2 ValveWater::setSizeInSpritesheet() {
	return glm::vec2(0.25f, 0.5f);
}

CollisionBox ValveWater::setCollisionBox() {
	CollisionBox collisionBox;

	if (sprite->animation() == CREATE) {
		if (orientation == 1) {
			collisionBox.min = COLLISION_BOX_MIN_CREATE_RIGHT;
			collisionBox.max = COLLISION_BOX_MAX_CREATE_RIGHT;
		}
		else {
			collisionBox.min = COLLISION_BOX_MIN_CREATE_LEFT;
			collisionBox.max = COLLISION_BOX_MAX_CREATE_LEFT;
		}
	}
	else {
		if (orientation == 1) {
			collisionBox.min = COLLISION_BOX_MIN_FLUSH_RIGHT;
			collisionBox.max = COLLISION_BOX_MAX_FLUSH_RIGHT;
		}
		else {
			collisionBox.min = COLLISION_BOX_MIN_FLUSH_LEFT;
			collisionBox.max = COLLISION_BOX_MAX_FLUSH_LEFT;
		}
	}
	return collisionBox;
}

void ValveWater::setAnimations() {
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(CREATE, 8);
	sprite->setAnimationSpeed(FLUSH, 8);

	//1==right, 0 == left
	if (orientation == 1) {
		sprite->addKeyframe(CREATE, glm::vec2(0.75f, 0.5f));
		sprite->addKeyframe(CREATE, glm::vec2(0.75f, 0.f));

		sprite->addKeyframe(FLUSH, glm::vec2(0.25f, 0.5f));
		sprite->addKeyframe(FLUSH, glm::vec2(0.25f, 0.0f));
	}
	else {
		sprite->addKeyframe(CREATE, glm::vec2(0.5f, 0.5f));
		sprite->addKeyframe(CREATE, glm::vec2(0.5f, 0.f));

		sprite->addKeyframe(FLUSH, glm::vec2(0.0f, 0.5f));
		sprite->addKeyframe(FLUSH, glm::vec2(0.0f, 0.0f));
	}

	sprite->changeAnimation(CREATE);
}

void ValveWater::render() {
	if (!restarting)
		sprite->render();
}

bool ValveWater::computeCooldown(int deltaTime) {

	animationCooldown -= deltaTime;
	if (animationCooldown <= 0)return true;
	else return false;
}

void ValveWater::childUpdate(int deltaTime) {

	if (sprite->animation() == CREATE) {

		if (animationCooldown == 0)animationCooldown = 1000;
		if (computeCooldown(deltaTime)) {
			sprite->changeAnimation(FLUSH);
			animationCooldown = 0;
		}
	}
	else if (sprite->animation() == FLUSH && !restarting) {
		
		if (animationCooldown == 0)animationCooldown = 3000;
		if (computeCooldown(deltaTime)) {
			animationCooldown = 0;
			restarting = true;
		}
	}
	else if (restarting) {

		if (animationCooldown == 0)animationCooldown = 3000;
		if (computeCooldown(deltaTime)) {
			restarting = false;
			sprite->changeAnimation(CREATE);
			animationCooldown = 0;
		}
	}
}

int ValveWater::damage() {
	return 15;
}

bool ValveWater::hit() {
	return !restarting;
}

void ValveWater::setOrientation(int orientation) {
	this->orientation = orientation;
}
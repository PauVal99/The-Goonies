#include <GL/glew.h>
#include <GL/glut.h>
#include "Drop.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 16)

#define DIE_TIME 0

#define FALL_SPEED 2

enum DropAnims
{
	CREATE, DROP, CRASH
};

string Drop::setImage() {
	return "images/Obstacles/Drop.png";
}

glm::vec2 Drop::setSize() {
	return glm::vec2(16, 16);
}

glm::vec2 Drop::setSizeInSpritesheet() {
	return glm::vec2(0.25f, 1);
}

CollisionBox Drop::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void Drop::setAnimations() {
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(CREATE, 2);
	sprite->addKeyframe(CREATE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(CREATE, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(DROP, 1);
	sprite->addKeyframe(DROP, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(CRASH, 1);
	sprite->addKeyframe(CRASH, glm::vec2(0.75f, 0.f));

	sprite->changeAnimation(CREATE);
	iniPos = getPosition();
}

void Drop::render() {
	if (!restarting)
		sprite -> render();
}

bool Drop::computeCooldown(int deltaTime) {

	animationCooldown -= deltaTime;
	if (animationCooldown <= 0)
		return true;
	else 
		return false;
}

void Drop::childUpdate(int deltaTime) {
	
	if (sprite->animation() == CREATE) {
		
		if (animationCooldown == 0)animationCooldown = 1000;
		if (computeCooldown(deltaTime)) {
			sprite->changeAnimation(DROP);
			animationCooldown = 0;
		}
	}
	else if (sprite->animation() == DROP) {
	
		position.y += FALL_SPEED;
		if (animationCooldown == 0)animationCooldown = 100;
		if (computeCooldown(deltaTime)) {
			if (collisionMap->collision(getCollisionBox())) {
				animationCooldown = 0;
				sprite->changeAnimation(CRASH);
			}
		}
	}
	else if (sprite->animation() == CRASH && !restarting) {

		if (animationCooldown == 0) animationCooldown = 200;
		if (computeCooldown(deltaTime)) {
			animationCooldown = 0;
			restarting = true;
		}
	}
	else if (restarting) {

		if(animationCooldown == 0)animationCooldown = 1000;
		if (computeCooldown(deltaTime)) {
			restarting = false;
			sprite->changeAnimation(CREATE);
			position = iniPos;
			animationCooldown = 0;
		}
	}
}

int Drop::damage() {
	return 10;
}

bool Drop::hit() {
	if(!restarting)
		sprite->changeAnimation(CRASH);
	return !restarting;
}
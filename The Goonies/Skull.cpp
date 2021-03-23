#include <GL/glew.h>
#include <GL/glut.h>
#include "Skull.h"

#define MOVE_SPEED 1

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(15, 19)

enum SkullAnims
{
	MOVE_LEFT, MOVE_RIGHT
};

int Skull::damage() {
	return 5;
}		

string Skull::setImage() {
	return "images/Skull.png";
}

glm::vec2 Skull::setSize() {
	return glm::ivec2(16, 20);
}

glm::vec2 Skull::setSizeInSpritesheet() {
	return glm::vec2(0.5, 0.5);
}

CollisionBox Skull::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void Skull::setAnimations() {
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 2);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
	
	sprite->setAnimationSpeed(MOVE_RIGHT, 2);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(MOVE_RIGHT);
}

void Skull::childUpdate() {
	if (position.x <= patrolPoint1) movingRight = true;
	else if (position.x >= patrolPoint2) movingRight = false;

	if (movingRight) {
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		position.x += MOVE_SPEED;
	}
	else {
		if (sprite->animation() != MOVE_LEFT) 
			sprite->changeAnimation(MOVE_LEFT);
		position.x -= MOVE_SPEED;
	}
}

void Skull::setPatrolPoints(const int patrolPoint1, const int patrolPoint2) {
	this -> patrolPoint1 = patrolPoint1;
	this -> patrolPoint2 = patrolPoint2;
}
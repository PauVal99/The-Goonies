#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"


#define COLLISION_BOX_MIN_CLOSED glm::ivec2(0, 0)
#define COLLISION_BOX_MAX_CLOSED glm::ivec2(60, 54)

#define COLLISION_BOX_MIN_OPEN glm::ivec2(15, 0)
#define COLLISION_BOX_MAX_OPEN glm::ivec2(35, 54)

enum DoorAnims
{
	CLOSED1KEY, CLOSED2KEY, OPENFRIEND, OPEN
};


string Door::setImage() {
	return "images/Doors/Doors.png";
}

glm::vec2 Door::setSize() {
	return glm::vec2(48, 54);
}

glm::vec2 Door::setSizeInSpritesheet() {
	return glm::vec2(0.25, 1);
}

CollisionBox Door::setCollisionBox() {
	CollisionBox collisionBox;

	if (open) {
		collisionBox.min = COLLISION_BOX_MIN_OPEN;
		collisionBox.max = COLLISION_BOX_MAX_OPEN;
	}
	else {
		collisionBox.min = COLLISION_BOX_MIN_CLOSED;
		collisionBox.max = COLLISION_BOX_MAX_CLOSED;
	}
	return collisionBox;
}

void Door::setAnimations() {
	
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(CLOSED1KEY, 1);
	sprite->addKeyframe(CLOSED1KEY, glm::vec2(0.f, 0.0f));

	sprite->setAnimationSpeed(CLOSED2KEY, 1);
	sprite->addKeyframe(CLOSED2KEY, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(OPENFRIEND, 1);
	sprite->addKeyframe(OPENFRIEND, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(OPEN, 1);
	sprite->addKeyframe(OPEN, glm::vec2(0.75f, 0.0f));

	sprite->changeAnimation(CLOSED1KEY);
}

void Door::childUpdate(int deltaTime) {
	
}


bool Door::playerInteraction(bool hasKey) {

	if (!itemCollected) {

		if (sprite->animation() == CLOSED1KEY && hasKey) {

			sprite->changeAnimation(OPENFRIEND);
			open = true;
			return true;
		}
		else if (sprite->animation() == OPENFRIEND) {
			sprite->changeAnimation(OPEN);
			itemCollected = true;
			return false;
		}
	}
}

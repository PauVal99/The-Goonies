#include <GL/glew.h>
#include <GL/glut.h>
#include "Door.h"
#include "SoundEngine.h"

#define COLLISION_BOX_MIN_CLOSED glm::ivec2(2, 32)
#define COLLISION_BOX_MAX_CLOSED glm::ivec2(12, 46)

#define COLLISION_BOX_MIN_OPEN glm::ivec2(32, 32)
#define COLLISION_BOX_MAX_OPEN glm::ivec2(48, 60)

enum DoorAnims {
	CLOSED1KEY, CLOSED2KEY, OPENFRIEND, OPEN
};

string Door::setImage() {
	return "images/Doors.png";
}

glm::vec2 Door::setSize() {
	return glm::vec2(64, 64);
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


	if (numberOfKeys == 1)
		sprite->changeAnimation(CLOSED1KEY);
	else
		sprite->changeAnimation(CLOSED2KEY);
	
}

void Door::setNumberOfKeys(int numKeys) {
	this->numberOfKeys = numKeys;
}

void Door::rescueFriend() {
	SoundEngine::getInstance()->playRescue();
	sprite->changeAnimation(OPEN);
	itemCollected = true;
}

bool Door::playerInteraction(bool hasKey) {
	if (!itemCollected) {
		if (sprite->animation() == CLOSED2KEY && hasKey) {
			sprite->changeAnimation(CLOSED1KEY);
			SoundEngine::getInstance()->playPutKey();
			return true;
		} else if (sprite->animation() == CLOSED1KEY && hasKey) {
			sprite->changeAnimation(OPENFRIEND);
			open = true;
			SoundEngine::getInstance()->playOpenDoor();
			return true;
		} else if (sprite->animation() == OPENFRIEND) {
			rescueFriend();
			return false;
		}
	}
	return true;
}

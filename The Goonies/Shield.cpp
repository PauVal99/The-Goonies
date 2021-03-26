#include "Shield.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 16)

string Shield::setImage() {

	return "images/PowerUps/Shield.png";
}

glm::vec2 Shield::setSize() {

	return glm::ivec2(16, 16);
}

glm::vec2 Shield::setSizeInSpritesheet() {

	return glm::vec2(1, 1);

}


CollisionBox Shield::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void Shield::setAnimations() {

}

void Shield::childUpdate(int deltaTime) {

}

void Shield::activatePowerUp(Player* player) {

	player->activateShield();
}
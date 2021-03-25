#include "VitalityPotion.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 16)

string VitalityPotion::setImage() {

	return "images/PowerUps/VitalityPotion.png";
}

glm::vec2 VitalityPotion::setSize() {

	return glm::ivec2(16, 16);
}

glm::vec2 VitalityPotion::setSizeInSpritesheet() {

	return glm::vec2(1, 1);

}


CollisionBox VitalityPotion::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void VitalityPotion::setAnimations() {

}

void VitalityPotion::childUpdate(int deltaTime) {

}

void VitalityPotion::activatePowerUp(Player* player) {

	player->activateVitalityPotion();
}
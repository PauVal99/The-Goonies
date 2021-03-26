#include "ExperiencePotion.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 16)

string ExperiencePotion::setImage() {

	return "images/PowerUps/ExperiencePotion.png";
}

glm::vec2 ExperiencePotion::setSize() {

	return glm::ivec2(16, 16);
}

glm::vec2 ExperiencePotion::setSizeInSpritesheet() {

	return glm::vec2(1, 1);

}


CollisionBox ExperiencePotion::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void ExperiencePotion::setAnimations() {

}

void ExperiencePotion::childUpdate(int deltaTime) {

}

void ExperiencePotion::activatePowerUp(Player* player) {

	player->activateExperiencePotion();
}
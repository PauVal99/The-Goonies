#include "PowerUp.h"

glm::vec2 PowerUp::setSize() {
	return glm::vec2(16, 16);
}

glm::vec2 PowerUp::setSizeInSpritesheet() {
	return glm::vec2(1, 1);
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

void PowerUp::take(Player* player) {
	activatePowerUp(player);
	end();
}
#include "HyperShoes.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 16)

string HyperShoes::setImage() {

	return "images/PowerUps/HyperShoes.png";
}

glm::vec2 HyperShoes::setSize() {

	return glm::ivec2(16, 16);
}

glm::vec2 HyperShoes::setSizeInSpritesheet() {

	return glm::vec2(1, 1);

}


CollisionBox HyperShoes::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void HyperShoes::setAnimations() {

}

void HyperShoes::childUpdate() {
	
}

void HyperShoes::activatePowerUp() {


}
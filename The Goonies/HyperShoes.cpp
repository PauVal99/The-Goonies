#include "HyperShoes.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(15, 19)

string HyperShoes::setImage() {

	return "images/Skull.png";
}

glm::vec2 HyperShoes::setSize() {

	return glm::ivec2(16, 20);

}

glm::vec2 HyperShoes::setSizeInSpritesheet() {

	return glm::vec2(0.5, 0.5);

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
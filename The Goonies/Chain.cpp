#include <GL/glew.h>
#include <GL/glut.h>
#include "Chain.h"

string Chain::setImage() {
	return "images/Obstacles/Chain.png";
}

glm::vec2 Chain::setSize() {
	return glm::vec2(32, 16);
}

glm::vec2 Chain::setSizeInSpritesheet() {
	return glm::vec2(1, 1);
}

CollisionBox Chain::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = glm::vec2(0,0);
	collisionBox.max = glm::vec2(0, 0);
	return collisionBox;
}
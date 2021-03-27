#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"


#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(15, 19)


string Key::setImage() {
	return "images/Key.png";
}

glm::vec2 Key::setSize() {
	return glm::vec2(16, 20);
}

glm::vec2 Key::setSizeInSpritesheet() {
	return glm::vec2(1, 1);
}

CollisionBox Key::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}


void Key::childUpdate(int deltaTime) {

}


#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"

string Key::setImage() {
	return "images/Key.png";
}

void Key::activatePowerUp(Player* player) {
	player->addKey();
}
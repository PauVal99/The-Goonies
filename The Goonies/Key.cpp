#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"

string Key::setImage() {
	return "images/Key.png";
}

bool Key::activatable(Player* player) {
	return !player->hasKey();
}

void Key::activatePowerUp(Player* player) {
	player->addKey();
}
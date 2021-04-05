#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"
#include "SoundEngine.h"

string Key::setImage() {
	return "images/PowerUps/Key.png";
}

bool Key::activatable(Player* player) {
	return !player->hasKey();
}

void Key::activatePowerUp(Player* player) {
	player->addKey();
}

void Key::playSound() {
	SoundEngine::getInstance()->playPickUpKey();
}
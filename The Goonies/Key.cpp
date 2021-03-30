#include <GL/glew.h>
#include <GL/glut.h>
#include "Key.h"

string Key::setImage() {
	return "images/PowerUps/Key.png";
}

bool Key::activatable(Player* player) {
	return !player->hasKey();
}

void Key::activatePowerUp(Player* player) {
	player->addKey();
}

void Key::childUpdate(int deltaTime) {
	++frames;
	if(frames >= 1000) 
		frames = 0; 

	if((frames/20) % 2 == 0)
		discard();
	else 
		resetColor();
}
#include "TimePowerUp.h"

string TimePowerUp::setImage() {
	return "images/PowerUps/Clock.png";
}

void TimePowerUp::activatePowerUp(Player* player) {
	player->activateTimePowerUp();
}
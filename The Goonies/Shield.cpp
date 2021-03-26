#include "Shield.h"

string Shield::setImage() {
	return "images/PowerUps/Shield.png";
}

void Shield::activatePowerUp(Player* player) {

	player->activateShield();
}
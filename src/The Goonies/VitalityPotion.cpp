#include "VitalityPotion.h"

string VitalityPotion::setImage() {
	return "images/PowerUps/VitalityPotion.png";
}

void VitalityPotion::activatePowerUp(Player* player) {
	player->activateVitalityPotion();
}
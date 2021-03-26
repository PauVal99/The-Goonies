#include "ExperiencePotion.h"

string ExperiencePotion::setImage() {
	return "images/PowerUps/ExperiencePotion.png";
}

void ExperiencePotion::activatePowerUp(Player* player) {
	player->activateExperiencePotion();
}
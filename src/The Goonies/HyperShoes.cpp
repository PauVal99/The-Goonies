#include "HyperShoes.h"

string HyperShoes::setImage() {
	return "images/PowerUps/HyperShoes.png";
}

void HyperShoes::activatePowerUp(Player* player) {
	player->activateHyperShoes();
}
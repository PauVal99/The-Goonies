#ifndef _VITALITYPOTION_INCLUDE
#define _VITALITYPOTION_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class VitalityPotion : public PowerUp {

public:
	void activatePowerUp(Player* player);

protected:
	string setImage();

};

#endif

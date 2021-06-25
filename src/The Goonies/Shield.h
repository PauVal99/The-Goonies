#ifndef _SHIELD_INCLUDE
#define _SHIELD_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class Shield : public PowerUp {

public:
	void activatePowerUp(Player* player);

protected:
	string setImage();

};

#endif
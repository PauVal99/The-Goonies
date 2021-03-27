#ifndef _TIMEPOWERUP_INCLUDE
#define _TIMEPOWERUP_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class TimePowerUp : public PowerUp {

public:
	void activatePowerUp(Player* player);

protected:
	string setImage();

};

#endif
#ifndef _EXPERIENCEPOTION_INCLUDE
#define _EXPERIENCEPOTION_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class ExperiencePotion : public PowerUp {

public:
	void activatePowerUp(Player* player);

protected:
	string setImage();
	
};

#endif

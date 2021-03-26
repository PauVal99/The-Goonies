#ifndef _HYPERSHOES_INCLUDE
#define _HYPERSHOES_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class HyperShoes : public PowerUp {

public:
	void activatePowerUp(Player* player);

protected:
	string setImage();

};

#endif
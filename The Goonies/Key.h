#ifndef _KEY_INCLUDE
#define _KEY_INCLUDE

#include "PowerUp.h"
#include "Player.h"

class Key : public PowerUp
{

public:
    void activatePowerUp(Player* player);

protected:
    virtual string setImage();

};

#endif
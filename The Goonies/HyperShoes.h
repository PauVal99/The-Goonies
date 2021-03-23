#ifndef _HYPERSHOES_INCLUDE
#define _HYPERSHOES_INCLUDE

#include "PowerUp.h";

class HyperShoes : public PowerUp {

public:
	void activatePowerUp();

protected:
	string setImage();
	glm::vec2 setSize();
	glm::vec2 setSizeInSpritesheet();
	void setAnimations();
    void childUpdate();
	CollisionBox setCollisionBox();
};

#endif
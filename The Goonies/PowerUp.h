#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE

#include "Sprite.h"
#include "CollisionMap.h"
#include "CollisionBox.h"



class PowerUp
{

public:
	

protected:
	Texture spritesheet;
	Sprite* sprite;
	CollisionMap* map;

public:
	PowerUp();
	virtual void init(const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram, const glm::ivec2& pos) = 0;
	void update(int deltaTime);
	void render();
	virtual void activatePowerUp() = 0;


private:
	
};


#endif // _POWERUP_INCLUDE
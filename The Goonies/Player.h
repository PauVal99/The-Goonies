#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "CollisionMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setCollisionMap(CollisionMap *collisionMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	glm::ivec2 getMinCollisionBox();
	glm::ivec2 getMaxCollisionBox();

private:
	bool jumping;
	glm::ivec2 tileMapOffset, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	CollisionMap *map;

};


#endif // _PLAYER_INCLUDE



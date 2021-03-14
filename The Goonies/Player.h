#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "CollisionMap.h"
#include "CollisionBox.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapOffset, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setCollisionMap(CollisionMap *collisionMap);
	void setPosition(const glm::vec2 &pos);
	
private:
	CollisionBox getCollisionBox();

private:
	bool jumping;
	glm::ivec2 tileMapOffset, posPlayer;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	CollisionMap *map;
};


#endif // _PLAYER_INCLUDE



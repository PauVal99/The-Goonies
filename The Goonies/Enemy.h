#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "CollisionMap.h"

class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setCollisionMap(CollisionMap* collisionMap);
	void setPosition(const glm::ivec2& pos);
	void setPatrolPoints(const int patrolPoint1, const int patrolPoint2);

private:
	glm::ivec2 tileMapDispl, posEnemy;
	int startY, patrolPoint1, patrolPoint2;
	bool movingRight = true;
	Texture spritesheet;
	Sprite* sprite;
	CollisionMap* map;
};


#endif



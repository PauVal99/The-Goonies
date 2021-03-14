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
	void setPosition(const glm::vec2& pos);
	void setPatrolPoints(const float patrolPoint1, const float patrolPoint2);

private:
	
	glm::ivec2 tileMapDispl, posEnemy;
	float patrolPoint1, patrolPoint2;
	int startY;
	bool movingRight = true;
	Texture spritesheet;
	Sprite* sprite;
	CollisionMap* map;

};


#endif



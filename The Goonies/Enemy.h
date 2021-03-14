#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"




class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setPatrolPoints(const glm::vec2& patrolPoint1, const glm::vec2& patrolPoint2);

private:
	
	glm::ivec2 tileMapDispl, posEnemy;
	glm::ivec2 patrolPoint1, patrolPoint2;
	int startY;
	bool movingRight = true;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif



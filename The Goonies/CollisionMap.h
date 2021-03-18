#ifndef _COLLISION_MAP_INCLUDE
#define _COLLISION_MAP_INCLUDE

#include <glm/glm.hpp>
#include <string>
#include "CollisionBox.h"

#define AIR 0
#define BLOCK 1
#define VINE 2

using namespace std;

struct Tiles
{
    glm::ivec2 min;
    glm::ivec2 max;
};

class CollisionMap
{

public:
	static CollisionMap *createCollisionMap(const string &levelFile);

	CollisionMap(const string &levelFile);
	~CollisionMap();
	
	int getTileSize() const { return tileSize; }
	void setPlayerCollisonBox(const CollisionBox &collisionBox);

    bool collision(const CollisionBox &collisionBox);
	bool onGround(const CollisionBox &collisionBox);
	glm::ivec2 onVine(const CollisionBox &collisionBox);
	glm::ivec2 aboveVine(const CollisionBox &collisionBox);
private:
	bool loadLevel(const string &levelFile);
	Tiles getTiles(const CollisionBox &collisionBox);

private:
	CollisionBox playerCollisionBox;
	glm::ivec2 mapSize;
	int tileSize;
	int *map;
};


#endif // _TILE_MAP_INCLUDE


#ifndef _COLLISION_MAP_INCLUDE
#define _COLLISION_MAP_INCLUDE

#include <glm/glm.hpp>
#include <string>
#include "CollisionBox.h"

enum {
	AIR, BLOCK, VINE, PORTAL
};

using namespace std;

struct Tiles
{
    glm::ivec2 min;
    glm::ivec2 max;
};

class CollisionMap
{

public:
	static CollisionMap *createCollisionMap(const string &levelFile, const glm::ivec2 &tileMapOffset);

	CollisionMap(const string &levelFile, const glm::ivec2 &tileMapOffset);
	~CollisionMap();
	
	int getTileSize() const { return tileSize; }

    bool collision(const CollisionBox &collisionBox);
	bool onGround(const CollisionBox &collisionBox);
	glm::ivec2 onVine(const CollisionBox &collisionBox);
	glm::ivec2 aboveVine(const CollisionBox &collisionBox);
	bool onPortal(const CollisionBox &collisionBox);
	void setStone(glm::ivec2 position);
	void updateStone(glm::ivec2 position, bool goingDown);
private:
	bool loadLevel(const string &levelFile);
	Tiles getTiles(const CollisionBox &collisionBox);

private:
	glm::ivec2 mapSize, collisionMapOffset;
	int tileSize;
	int *map;
};

#endif // _TILE_MAP_INCLUDE
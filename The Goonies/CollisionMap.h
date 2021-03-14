#ifndef _COLLISION_MAP_INCLUDE
#define _COLLISION_MAP_INCLUDE

#include <glm/glm.hpp>
#include <string>

using namespace std;

class CollisionMap
{

public:
	static CollisionMap *createCollisionMap(const string &levelFile);

	CollisionMap(const string &levelFile);
	~CollisionMap();
	
	int getTileSize() const { return tileSize; }

    bool collision(const glm::ivec2 &min, const glm::ivec2 &max);
	
private:
	bool loadLevel(const string &levelFile);

private:
	glm::ivec2 mapSize;
	int tileSize;
	int *map;
};


#endif // _TILE_MAP_INCLUDE



#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <map>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "CollisionMap.h"
#include "Player.h"

#define OFFSET glm::vec2(0, 0)
#define TILE_SIZE 16

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Scene
{

public:
	Scene();
	~Scene();
	void init();
	void update(int deltaTime);
	void render();

protected:
	virtual void setTileMaps() = 0;
	virtual glm::ivec2 setPlayerPosition() = 0;
	virtual void setEnemies() = 0;
	virtual void enemiesUpdate(const int &deltaTime) = 0;
	virtual void enemiesRender() = 0;

private:
	void initShaders();

protected:
	std::map<int, TileMap*> tileMaps;
	CollisionMap* collisionMap;

	ShaderProgram texProgram;

private:
	float currentTime;
	glm::mat4 projection;

	Player* player;
};


#endif // _SCENE_INCLUDE


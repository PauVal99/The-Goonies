#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <map>
#include <vector>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "TileMap.h"
#include "CollisionMap.h"
#include "Player.h"
#include "Door.h"
#include "Key.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Camera.h"
#include "Obstacle.h"

#define OFFSET glm::vec2(0, 0)
#define TILE_SIZE 16

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Scene
{

public:
	Scene();
	~Scene();
	void init(Player* player);
	void update(int deltaTime);
	void render();

protected:
	virtual void setTileMaps() = 0;
	virtual glm::ivec2 setPlayerPosition() = 0;
	virtual void setEnemies() {}
	virtual void setPowerUps() {}
	virtual void setDoors() {}
	virtual void setObstacles() {}
	void createSkull(glm::ivec2 pos, glm::ivec2 patrolPoints);

private:
	void initShaders();
	void updateActors(int deltaTime);

protected:
	Player* player;
	std::map<int, TileMap*> tileMaps;
	CollisionMap* collisionMap;
	std::vector<Enemy*> enemies;
	std::vector<PowerUp*> powerUps;
	std::vector<Door*> doors;
	std::vector<Obstacle*>obstacles;

	ShaderProgram texProgram;

private:
	bool collision(const CollisionBox &collisionBox1, const CollisionBox &collisionBox2);

private:
	float currentTime;
	glm::mat4 projection;
	Camera* camera;

};


#endif // _SCENE_INCLUDE


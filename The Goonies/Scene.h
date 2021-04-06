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
#include "GUI.h"

#define OFFSET glm::ivec2(0, 44)
#define TILE_SIZE 16

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Scene
{

public:
	Scene();
	~Scene();
	virtual void init(Player* player);
	virtual void update(int deltaTime);
	virtual void render();

protected:
	virtual void setTileMaps() {};
	virtual glm::ivec2 setPlayerPosition() { return glm::ivec2(-1, -1); };
	virtual void setEnemies() {};
	virtual void setPowerUps() {};
	virtual void setDoors() {};
	virtual void setObstacles() {};
	void createSkull(glm::ivec2 pos, glm::ivec2 patrolPoints);
	void initShaders();

protected:
	Player* player;
	std::map<int, TileMap*> tileMaps;
	CollisionMap* collisionMap;
	std::vector<Enemy*> enemies;
	std::vector<PowerUp*> powerUps;
	std::vector<Door*> doors;
	std::vector<Obstacle*> obstacles;

	ShaderProgram texProgram;

protected:
	float currentTime;
	glm::mat4 projection;

private:
	void updateActors(int deltaTime);
	int getFriendsToSave() { return doors.size(); };
	bool collision(const CollisionBox& collisionBox1, const CollisionBox& collisionBox2);

private:
	int savedFriends = 0;
	int prevF = false, prevUp = false;
	Camera* camera;
	GUI* gui;

};


#endif // _SCENE_INCLUDE


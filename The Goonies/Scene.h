#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "CollisionMap.h"
#include "Player.h"
#include "Enemy.h"
#include <map>


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

protected:
	void initShaders();

protected:
	std::map<int, TileMap*> tileMaps;
	CollisionMap * collisionMap;
	Player* player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE


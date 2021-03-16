#ifndef _REDSCENE_INCLUDE
#define _REDSCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "CollisionMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"


class RedScene: public Scene
{

public:
	void init();
	void update(int deltaTime);
	void render();

private:


private:
	Enemy* enemy;
};


#endif // _SCENE_INCLUDE



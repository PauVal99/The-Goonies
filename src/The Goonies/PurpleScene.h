#ifndef _PURPLESCENE_INCLUDE
#define _PURPLESCENE_INCLUDE

#include "Scene.h"

class PurpleScene : public Scene
{
protected:
	void setTileMaps();
	glm::ivec2 setPlayerPosition();
	void setEnemies();
	void setPowerUps();
	void setDoors();
	void setObstacles();
};


#endif // _SCENE_INCLUDE
#ifndef _YELLOWSCENE_INCLUDE
#define _YELLOWSCENE_INCLUDE

#include "Scene.h"

class YellowScene : public Scene
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

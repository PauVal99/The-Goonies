#ifndef _ORANGESCENE_INCLUDE
#define _ORANGESCENE_INCLUDE

#include "Scene.h"

class OrangeScene : public Scene
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

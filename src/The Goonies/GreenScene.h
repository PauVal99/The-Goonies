#ifndef _GREENSCENE_INCLUDE
#define _GREENSCENE_INCLUDE

#include "Scene.h"

class GreenScene : public Scene
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

#ifndef _REDSCENE_INCLUDE
#define _REDSCENE_INCLUDE

#include "Scene.h"

class RedScene: public Scene
{
protected:
	void setTileMaps();
	glm::ivec2 setPlayerPosition();
	void setEnemies();
	void setPowerUps();

};


#endif // _SCENE_INCLUDE



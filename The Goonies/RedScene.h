#ifndef _REDSCENE_INCLUDE
#define _REDSCENE_INCLUDE

#include "Skull.h"
#include "Scene.h"

class RedScene: public Scene
{
public:
	RedScene::~RedScene();

protected:
	void setTileMaps();
	glm::ivec2 setPlayerPosition();
	void setEnemies();
	void enemiesUpdate(const int &deltaTime);
	void enemiesRender();

private:
	Skull* skull;
};


#endif // _SCENE_INCLUDE



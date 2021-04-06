#ifndef _START_INCLUDE
#define _START_INCLUDE

#include "Scene.h"

class Start : public Scene
{
protected:
	void init(Player* player);
	void update(int deltaTime);
	void render();

private:
	Texture startTexture;
	Sprite* start;

};


#endif // _SCENE_INCLUDE

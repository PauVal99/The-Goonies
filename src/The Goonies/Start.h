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
	int cooldown = 5000; 
	Texture startTexture;
	Sprite* start;

	Texture instructionsTexture;
	Sprite* instructions;

};


#endif // _SCENE_INCLUDE

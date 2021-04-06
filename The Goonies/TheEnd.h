#ifndef _THEEND_INCLUDE
#define _THEEND_INCLUDE

#include "Scene.h"

class TheEnd : public Scene
{
protected:
	void init(Player* player);
	void update(int deltaTime);
	void render();

private:
    Texture theEndTexture;
    Sprite* theEnd;

};


#endif // _SCENE_INCLUDE

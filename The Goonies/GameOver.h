#ifndef _GAMEOVER_INCLUDE
#define _GAMEOVER_INCLUDE

#include "Scene.h"

class GameOver : public Scene
{
protected:
	void init(Player* player);
	void update(int deltaTime);
	void render();

private:
    Texture gameOverTexture;
    Sprite* gameOver;

};


#endif // _SCENE_INCLUDE

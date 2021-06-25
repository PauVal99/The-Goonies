#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include <queue>
#include <memory>
#include "Scene.h"

#define  GLUT_KEY_SPACEBAR 32

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 320 + 44 + 24

// Game is a singleton (a class with a single instance) that represents our whole application

class Game
{

public:
	Game() {}
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	void start();
	void gameOver();
	void nextScene();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	int gameOverCooldown = 5000, theEndCooldown = 5000;
	bool bPlay = true, next = false, restartGame = false, gameOverBool = false, startBool = false;
	std::queue<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> currentScene;
	Player player;
	bool keys[256], specialKeys[256];

};


#endif // _GAME_INCLUDE



#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "RedScene.h"
#include "GreenScene.h"
#include "PurpleScene.h"
#include "YellowScene.h"
#include "OrangeScene.h"

void Game::init()
{
	bPlay = true;

	player = Player();

	scenes.push(std::make_shared<PurpleScene>());
	scenes.push(std::make_shared<YellowScene>());
	scenes.push(std::make_shared<OrangeScene>());
	scenes.push(std::make_shared<GreenScene>());
	scenes.push(std::make_shared<RedScene>());
	
	scenes.push(std::make_shared<PurpleScene>());
	
	scenes.front()->init(&player);
}

void Game::nextScene() {
	next = true;
}

void Game::restart() {
	restartGame = true;
}

bool Game::update(int deltaTime)
{
	if(next) {
		next = false;
		scenes.pop();
		scenes.front()->init(&player);
	} else if(restartGame) {
		restartGame = false;
		while(!scenes.empty())
			scenes.pop();
		init();
	}

	scenes.front()->update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	scenes.front()->render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}






#include <GL/glew.h>
#include <GL/glut.h>
#include <irrKlang.h>
#include "Game.h"
#include "RedScene.h"
#include "GreenScene.h"
#include "PurpleScene.h"
#include "YellowScene.h"
#include "OrangeScene.h"
#include "GameOver.h"
#include "SoundEngine.h"

void Game::init()
{
	player = Player();

	scenes.push(std::make_shared<PurpleScene>());
	scenes.push(std::make_shared<YellowScene>());
	scenes.push(std::make_shared<OrangeScene>());
	scenes.push(std::make_shared<GreenScene>());
	scenes.push(std::make_shared<RedScene>());
	
	currentScene = scenes.front();
	currentScene->init(&player);
	SoundEngine::getInstance()->stopAllSounds();
	SoundEngine::getInstance()->playMainTheme();
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
		SoundEngine::getInstance()->playPortal();
		scenes.pop();
		currentScene = scenes.front();
		currentScene->init(&player);
	} else if(restartGame) {
		if(gameOverCooldown == 5000) {
			currentScene = std::make_shared<GameOver>();
			currentScene->init(&player);
		}
		gameOverCooldown -= deltaTime;
		if(gameOverCooldown <= 0) {
			gameOverCooldown = 5000;
			restartGame = false;
			while(!scenes.empty())
				scenes.pop();
			init();
		}
	}
	currentScene->update(deltaTime);
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	currentScene->render();
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






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
#include "TheEnd.h"
#include "SoundEngine.h"

void Game::init()
{
	player = Player();

	scenes.push(std::make_shared<RedScene>());
	scenes.push(std::make_shared<GreenScene>());
	scenes.push(std::make_shared<YellowScene>());
	scenes.push(std::make_shared<PurpleScene>());
	scenes.push(std::make_shared<OrangeScene>());
	
	currentScene = scenes.front();
	currentScene->init(&player);
	SoundEngine::getInstance()->stopAllSounds();
	SoundEngine::getInstance()->playMainTheme();
}

void Game::nextScene() {
	next = true;
}

void Game::gameOver() {
	gameOverBool = true;
	SoundEngine::getInstance()->stopAllSounds();
	SoundEngine::getInstance()->playGameOver();
}

bool Game::update(int deltaTime)
{
	if(theEndCooldown < 5000) {
		theEndCooldown -= deltaTime;
		if(theEndCooldown <= 0) {
			theEndCooldown = 5000;
			restartGame = true;
		}
	}

	if(gameOverCooldown < 5000) {
		gameOverCooldown -= deltaTime;
		if(gameOverCooldown <= 0) {
			gameOverCooldown = 5000;
			restartGame = true;
		}
	}

	if(next) {
		next = false;
		SoundEngine::getInstance()->playPortal();
		scenes.pop();
		if(scenes.empty()) {
			theEndCooldown -= deltaTime;
			SoundEngine::getInstance()->stopAllSounds();
			SoundEngine::getInstance()->playTheEnd();
			currentScene = std::make_shared<TheEnd>();
			currentScene->init(&player);
		} else {
			currentScene = scenes.front();
			currentScene->init(&player);
		}
	} else if(gameOverBool) {
		gameOverBool = false;
		gameOverCooldown -= deltaTime;
		currentScene = std::make_shared<GameOver>();
		currentScene->init(&player);
	} else if(restartGame) {
		restartGame = false;
		while(!scenes.empty())
			scenes.pop();
		init();
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






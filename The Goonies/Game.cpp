#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "RedScene.h"

void Game::init()
{
	bPlay = true;

	player = new Player();

	scenes.push(new RedScene());
	scenes.push(new RedScene());

	setCurrentScene(scenes.front());
}

void Game::nextScene() {
	delete currentScene;
	scenes.pop();
	setCurrentScene(scenes.front());
}

void Game::setCurrentScene(Scene* scene) {
	currentScene = scene;
	currentScene->init(player);
}

void Game::restart()
{
	while(!scenes.empty()) {
		delete scenes.front();
		scenes.pop();
	}
	
	init();
}

bool Game::update(int deltaTime)
{
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






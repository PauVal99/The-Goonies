#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "RedScene.h"
#include "Scene.h"
#include "Game.h"


#define OFFSET_X 0
#define OFFSET_Y 0

#define INIT_PLAYER_X_TILES 6
#define INIT_PLAYER_Y_TILES 6

#define TILE_SIZE 16


void RedScene::init()
{
	initShaders();

	TileMap* map;

	map = TileMap::createTileMap("levels/RedLevel/Ground.txt", glm::vec2(0, 0), texProgram);
	map->layer = 1;
	tileMaps[map->layer] = map;

	map = TileMap::createTileMap("levels/RedLevel/Platforms.txt", glm::vec2(0, 0), texProgram);
	map->layer = 2;
	tileMaps[map->layer] = map;

	collisionMap = CollisionMap::createCollisionMap("levels/test.cm");

	player = new Player();
	player->init(glm::ivec2(OFFSET_X, OFFSET_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * TILE_SIZE, INIT_PLAYER_Y_TILES * TILE_SIZE));
	player->setCollisionMap(collisionMap);

	enemy = new Enemy();
	enemy->init(glm::ivec2(OFFSET_X, OFFSET_Y), texProgram);
	enemy->setPosition(glm::vec2(8 * 16, 7 * 16));
	enemy->setPatrolPoints(8 * 16, 14 * 16);
	enemy->setCollisionMap(collisionMap);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void RedScene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	enemy->update(deltaTime);
}

void RedScene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	for (auto keyValue : tileMaps)
		keyValue.second->render();
	player->render();
	enemy->render();
}






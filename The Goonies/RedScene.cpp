#include <glm/gtc/matrix_transform.hpp>
#include "RedScene.h"
#include "Game.h"

RedScene::~RedScene() {
	delete enemy;
}

void RedScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/RedLevel/Ground.tm", 1, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	tileMap = TileMap::createTileMap("levels/RedLevel/Platforms.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	collisionMap = CollisionMap::createCollisionMap("levels/RedLevel/RedLevel.cm");
}

glm::ivec2 RedScene::setPlayerPosition() {
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void RedScene::setEnemies() {
	enemy = new Enemy();
	enemy->init(OFFSET, texProgram);
	enemy->setPosition(glm::ivec2(8, 7) * TILE_SIZE);
	enemy->setPatrolPoints(8 * TILE_SIZE, 14 * TILE_SIZE);
	enemy->setCollisionMap(collisionMap);
}

void RedScene::enemiesUpdate(const int &deltaTime) {
	enemy->update(deltaTime);
}

void RedScene::enemiesRender()
{
	enemy->render();
}






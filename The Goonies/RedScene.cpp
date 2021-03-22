#include <glm/gtc/matrix_transform.hpp>
#include "RedScene.h"

RedScene::~RedScene() {
	delete skull;
}

void RedScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/RedLevel/RedLevel.tm", 1, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	collisionMap = CollisionMap::createCollisionMap("levels/RedLevel/RedLevel.cm");
}

glm::ivec2 RedScene::setPlayerPosition() {
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void RedScene::setEnemies() {
	skull = new Skull();
	skull->init(glm::ivec2(8, 7) * TILE_SIZE, OFFSET, collisionMap, texProgram);
	skull->setPatrolPoints(8 * TILE_SIZE, 14 * TILE_SIZE);
}

void RedScene::enemiesUpdate(const int &deltaTime) {
	skull->update(deltaTime);
}

void RedScene::enemiesRender() {
	skull->render();
}






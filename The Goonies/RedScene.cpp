#include <glm/gtc/matrix_transform.hpp>
#include "RedScene.h"
#include "Skull.h"

void RedScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/red/Red.tm", 1, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	collisionMap = CollisionMap::createCollisionMap("levels/red/Red.cm");
}

glm::ivec2 RedScene::setPlayerPosition() {
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void RedScene::setEnemies() {
	Skull* skull = new Skull();
	skull->init(glm::ivec2(8, 8) * TILE_SIZE, OFFSET, collisionMap, texProgram);
	skull->setPatrolPoints(8 * TILE_SIZE, 14 * TILE_SIZE);
	enemies.push_back(skull);
}
#include <glm/gtc/matrix_transform.hpp>

#include "RedScene.h"
#include "Skull.h"
#include "HyperShoes.h"
#include "Shield.h"
#include "TimePowerUp.h"
#include "VitalityPotion.h"
#include "ExperiencePotion.h"

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
	skull->init(glm::ivec2(8, 8) * TILE_SIZE, OFFSET, texProgram);
	skull->setCollisionMap(collisionMap);
	skull->setPatrolPoints(8 * TILE_SIZE, 14 * TILE_SIZE);
	enemies.push_back(skull);
}

void RedScene::setPowerUps() {
	HyperShoes* hypershoes = new HyperShoes();
	hypershoes->init(glm::ivec2(10, 14) * TILE_SIZE, OFFSET, texProgram);

	powerUps.push_back(hypershoes);

	Shield* shield = new Shield();
	shield->init(glm::ivec2(14, 14) * TILE_SIZE, OFFSET, texProgram);

	powerUps.push_back(shield);

	VitalityPotion* vitalityPotion = new VitalityPotion();
	vitalityPotion->init(glm::ivec2(18, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(vitalityPotion);

	ExperiencePotion* experiencePotion = new ExperiencePotion();
	experiencePotion->init(glm::ivec2(22, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(experiencePotion);

	TimePowerUp* timePowerUp = new TimePowerUp();
	timePowerUp->init(glm::ivec2(26, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(timePowerUp);
}
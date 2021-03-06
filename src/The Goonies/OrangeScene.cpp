#include <glm/gtc/matrix_transform.hpp>

#include "OrangeScene.h"
#include "Key.h"
#include "Door.h"
#include "Skull.h"
#include "Bat.h"
#include "HyperShoes.h"
#include "Shield.h"
#include "TimePowerUp.h"
#include "VitalityPotion.h"
#include "ExperiencePotion.h"
#include "Drop.h"
#include "ValveWater.h"
#include "Stone.h"

void OrangeScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/orange/Orange_TM.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	collisionMap = CollisionMap::createCollisionMap("levels/orange/Orange_CM.cm", OFFSET);
}

glm::ivec2 OrangeScene::setPlayerPosition() {
	return glm::ivec2(1, 1) * TILE_SIZE;
}

void OrangeScene::setEnemies() {
	Bat* bat = new Bat();
	bat->init(glm::ivec2(24, 8) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(83, 3) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	createSkull(glm::ivec2(2, 8), glm::ivec2(2, 11));
	createSkull(glm::ivec2(1, 12), glm::ivec2(1, 14));
	createSkull(glm::ivec2(1, 17), glm::ivec2(1, 14));
	createSkull(glm::ivec2(17, 3), glm::ivec2(17, 30));
	createSkull(glm::ivec2(39, 3), glm::ivec2(39, 48));
	createSkull(glm::ivec2(42, 17), glm::ivec2(42, 57));
	createSkull(glm::ivec2(52, 6), glm::ivec2(52, 61));
	createSkull(glm::ivec2(65, 17), glm::ivec2(65, 79));
	createSkull(glm::ivec2(83, 17), glm::ivec2(83, 93));
	createSkull(glm::ivec2(67, 3), glm::ivec2(67, 79));
	createSkull(glm::ivec2(70, 8), glm::ivec2(70, 85));

}

void OrangeScene::setPowerUps() {

	TimePowerUp* timePowerUp = new TimePowerUp();
	timePowerUp->init(glm::ivec2(6, 17) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(timePowerUp);

	VitalityPotion* vitalityPotion = new VitalityPotion();
	vitalityPotion->init(glm::ivec2(35, 8) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(vitalityPotion);

	Shield* shield = new Shield();
	shield->init(glm::ivec2(46, 3) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(shield);

	Key* key = new Key();
	key->init(glm::ivec2(19, 3) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(60, 17) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(68, 17) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(75, 8) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

}

void OrangeScene::setDoors() {

	Door* door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(59, 4) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(2);
	door->init(glm::ivec2(66, 1) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(90, 15) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

}

void OrangeScene::setObstacles() {

	Drop* drop = new Drop();
	drop->init(glm::ivec2(17, 6) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(23, 15) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(46, 6) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(82, 6) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(37, 16) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(40, 16) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(44, 16) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(47, 16) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(56, 11) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(59, 11) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(65, 11) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);
}
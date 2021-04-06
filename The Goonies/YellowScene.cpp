#include <glm/gtc/matrix_transform.hpp>

#include "YellowScene.h"
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

void YellowScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/yellow/Yellow_TM.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;


	collisionMap = CollisionMap::createCollisionMap("levels/yellow/Yellow_CM.cm", OFFSET);
}

glm::ivec2 YellowScene::setPlayerPosition() {
	return glm::ivec2(8, 2) * TILE_SIZE;
}

void YellowScene::setEnemies() {
	createSkull(glm::ivec2(1, 8), glm::ivec2(1, 7));
	createSkull(glm::ivec2(10, 8), glm::ivec2(10, 20));
	createSkull(glm::ivec2(23, 8), glm::ivec2(23, 26));
	createSkull(glm::ivec2(23, 32), glm::ivec2(23, 30));
	createSkull(glm::ivec2(7, 59), glm::ivec2(7, 18));
	createSkull(glm::ivec2(3, 66), glm::ivec2(3, 14));
	createSkull(glm::ivec2(17, 66), glm::ivec2(17, 25));
}

void YellowScene::setPowerUps() {
	Key* key = new Key();
	key->init(glm::ivec2(6, 16) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(29, 40) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(27, 66) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	Shield* shield = new Shield();
	shield->init(glm::ivec2(11, 16) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(shield);

	TimePowerUp* timePowerUp = new TimePowerUp();
	timePowerUp->init(glm::ivec2(21, 32) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(timePowerUp);
}

void YellowScene::setDoors() {
	Door* door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(27, 6) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(6, 32) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(3, 45) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);
}

void YellowScene::setObstacles() {

	Stone* stone = new Stone();
	stone->init(glm::ivec2(22, 58) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	stone->changeAnimation(3);
	obstacles.push_back(stone);


	ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(2, 33) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(5, 39) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(15, 39) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	Drop* drop = new Drop();
	drop->init(glm::ivec2(27, 35) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(10, 62) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);
}
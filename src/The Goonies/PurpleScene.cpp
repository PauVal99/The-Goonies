#include <glm/gtc/matrix_transform.hpp>

#include "PurpleScene.h"
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

void PurpleScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/purple/Purple_TM.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;

	collisionMap = CollisionMap::createCollisionMap("levels/purple/Purple_CM.cm", OFFSET);
}

glm::ivec2 PurpleScene::setPlayerPosition() {
	return glm::ivec2(1, 15) * TILE_SIZE;
}

void PurpleScene::setEnemies() {
	createSkull(glm::ivec2(12, 16), glm::ivec2(12, 17));
	createSkull(glm::ivec2(1, 8), glm::ivec2(1, 11));
	createSkull(glm::ivec2(47, 16), glm::ivec2(47, 57));
	createSkull(glm::ivec2(55, 8), glm::ivec2(55, 61));
	createSkull(glm::ivec2(69, 17), glm::ivec2(69, 78));
	createSkull(glm::ivec2(82, 17), glm::ivec2(82, 90));
	createSkull(glm::ivec2(84, 3), glm::ivec2(84, 90));

	Bat* bat = new Bat();
	bat->init(glm::ivec2(18, 16) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(36, 16) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(80, 10) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);
}

void PurpleScene::setPowerUps() {

	Key* key = new Key();
	key->init(glm::ivec2(67, 17) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(92, 17) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(60, 16) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	Shield* shield = new Shield();
	shield->init(glm::ivec2(2, 3) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(shield);

	ExperiencePotion* experiencePotion = new ExperiencePotion();
	experiencePotion->init(glm::ivec2(59, 4) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(experiencePotion);

	HyperShoes* hyperShoes = new HyperShoes();
	hyperShoes->init(glm::ivec2(28, 16) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(hyperShoes);
}

void PurpleScene::setDoors() {
	Door* door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(27, 1) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(65, 2) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(2);
	door->init(glm::ivec2(91, 1) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);
}

void PurpleScene::setObstacles() {
	Stone* stone = new Stone();
	stone->init(glm::ivec2(41, 8) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	stone->changeAnimation(2);
	obstacles.push_back(stone);

	stone = new Stone();
	stone->init(glm::ivec2(17, 8) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	stone->changeAnimation(2);
	obstacles.push_back(stone);

	ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(38, 3) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(44, 3) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(47, 3) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(53, 3) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	Drop* drop = new Drop();
	drop->init(glm::ivec2(78, 9) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(83, 9) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);
}
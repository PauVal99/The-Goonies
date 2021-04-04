#include <glm/gtc/matrix_transform.hpp>

#include "RedScene.h"
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

void RedScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/red/Red.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;
	

	collisionMap = CollisionMap::createCollisionMap("levels/red/Red.cm", OFFSET);
}

glm::ivec2 RedScene::setPlayerPosition() {
	return glm::ivec2(4, 8) * TILE_SIZE;
}

void RedScene::setEnemies() {
	createSkull(glm::ivec2(2, 14), glm::ivec2(2, 18));
	createSkull(glm::ivec2(26, 9), glm::ivec2(26, 37));
	createSkull(glm::ivec2(45, 9), glm::ivec2(45, 59));
	createSkull(glm::ivec2(40, 4), glm::ivec2(40, 51));
	createSkull(glm::ivec2(68, 4), glm::ivec2(68, 75));
	createSkull(glm::ivec2(68, 16), glm::ivec2(68, 78));
	createSkull(glm::ivec2(85,10), glm::ivec2(85, 93));
	createSkull(glm::ivec2(83, 4), glm::ivec2(83, 91));

	/*Bat* bat = new Bat();
	bat->init(glm::ivec2(16, 6) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);*/
}

void RedScene::setPowerUps() {
	HyperShoes* hypershoes = new HyperShoes();
	hypershoes->init(glm::ivec2(10, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(hypershoes);

	Shield* shield = new Shield();
	shield->init(glm::ivec2(8, 9) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(shield);

	/*
	VitalityPotion* vitalityPotion = new VitalityPotion();
	vitalityPotion->init(glm::ivec2(18, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(vitalityPotion);

	ExperiencePotion* experiencePotion = new ExperiencePotion();
	experiencePotion->init(glm::ivec2(22, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(experiencePotion);

	TimePowerUp* timePowerUp = new TimePowerUp();
	timePowerUp->init(glm::ivec2(26, 14) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(timePowerUp); */

	Key* key = new Key();
	key->init(glm::ivec2(57, 4) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(66, 4) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(82, 10) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);
}

void RedScene::setDoors() {
	Door* door = new Door();
	door->init(glm::ivec2(65, 14) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->init(glm::ivec2(80, 2) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);
}

void RedScene::setObstacles() {

	Drop* drop = new Drop();
	drop->init(glm::ivec2(25, 12) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(39, 7) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(67, 7) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(80, 13) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	/*ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(18, 12) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);*/

	/*Stone* stone = new Stone();
	stone->init(glm::ivec2(24, 6) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	obstacles.push_back(stone);*/
}
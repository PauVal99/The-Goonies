#include <glm/gtc/matrix_transform.hpp>

#include "GreenScene.h"
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

void GreenScene::setTileMaps() {
	TileMap* tileMap = TileMap::createTileMap("levels/green/Green_TM.tm", 2, OFFSET, texProgram);
	tileMaps[tileMap->getLayer()] = tileMap;


	collisionMap = CollisionMap::createCollisionMap("levels/green/Green_CM.cm", OFFSET);
}

glm::ivec2 GreenScene::setPlayerPosition() {
	return glm::ivec2(1, 2) * TILE_SIZE;
}

void GreenScene::setEnemies() {
	createSkull(glm::ivec2(8, 11), glm::ivec2(8, 20));
	createSkull(glm::ivec2(23, 11), glm::ivec2(23, 30));
	createSkull(glm::ivec2(35, 18), glm::ivec2(35, 45));
	createSkull(glm::ivec2(49, 18), glm::ivec2(49, 59));
	createSkull(glm::ivec2(38, 6), glm::ivec2(38, 56));
	createSkull(glm::ivec2(52, 6), glm::ivec2(52, 61));
	createSkull(glm::ivec2(68, 18), glm::ivec2(68, 77));
	createSkull(glm::ivec2(79, 8), glm::ivec2(79, 93));

	Bat* bat = new Bat();
	bat->init(glm::ivec2(15, 3) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(42, 17) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(75, 17) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);

	bat = new Bat();
	bat->init(glm::ivec2(78, 15) * TILE_SIZE, OFFSET, texProgram);
	bat->setCollisionMap(collisionMap);
	bat->setPlayer(player);
	enemies.push_back(bat);
}

void GreenScene::setPowerUps() {
	ExperiencePotion* experiencePotion = new ExperiencePotion();
	experiencePotion->init(glm::ivec2(25, 3) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(experiencePotion);

	VitalityPotion* vitalityPotion = new VitalityPotion();
	vitalityPotion->init(glm::ivec2(35, 6) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(vitalityPotion);

	Key* key = new Key();
	key->init(glm::ivec2(61, 18) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(86, 3) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);

	key = new Key();
	key->init(glm::ivec2(67, 8) * TILE_SIZE, OFFSET, texProgram);
	powerUps.push_back(key);
}

void GreenScene::setDoors() {
	Door* door = new Door();
	door->setNumberOfKeys(1);
	door->init(glm::ivec2(34, 9) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);

	door = new Door();
	door->setNumberOfKeys(2);
	door->init(glm::ivec2(65, 16) * TILE_SIZE, OFFSET, texProgram);
	doors.push_back(door);
}

void GreenScene::setObstacles() {
	Stone* stone = new Stone();
	stone->init(glm::ivec2(2, 7) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	stone->changeAnimation(1);
	obstacles.push_back(stone);

	stone = new Stone();
	stone->init(glm::ivec2(86, 12) * TILE_SIZE, OFFSET, texProgram);
	stone->setCollisionMap(collisionMap);
	stone->changeAnimation(1);
	obstacles.push_back(stone);
	
	Drop* drop = new Drop();
	drop->init(glm::ivec2(55, 9) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(42, 14) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(57, 1) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(91, 1) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(82, 11) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	drop = new Drop();
	drop->init(glm::ivec2(90, 11) * TILE_SIZE, OFFSET, texProgram);
	drop->setCollisionMap(collisionMap);
	obstacles.push_back(drop);

	ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(6, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(9, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(14, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(17, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(22, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(25, 15) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(69, 1) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(77, 7) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(80, 7) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);
}
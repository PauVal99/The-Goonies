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


	collisionMap = CollisionMap::createCollisionMap("levels/yellow/Yellow_CM.cm");
}

glm::ivec2 YellowScene::setPlayerPosition() {
	return glm::ivec2(2, 2) * TILE_SIZE;
}

void YellowScene::setEnemies() {

}

void YellowScene::setPowerUps() {

}

void YellowScene::setDoors() {

}

void YellowScene::setObstacles() {

	ValveWater* valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(2, 29) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(5, 35) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(1);
	valveWater->init(glm::ivec2(18, 35) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

	valveWater = new ValveWater();
	valveWater->setOrientation(0);
	valveWater->init(glm::ivec2(15, 35) * TILE_SIZE, OFFSET, texProgram);
	valveWater->setCollisionMap(collisionMap);
	obstacles.push_back(valveWater);

}
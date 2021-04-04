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


	collisionMap = CollisionMap::createCollisionMap("levels/orange/Orange_CM.cm");
}

glm::ivec2 OrangeScene::setPlayerPosition() {
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void OrangeScene::setEnemies() {

}

void OrangeScene::setPowerUps() {

}

void OrangeScene::setDoors() {

}

void OrangeScene::setObstacles() {


}
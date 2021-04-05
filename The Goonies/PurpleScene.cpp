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
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void PurpleScene::setEnemies() {

}

void PurpleScene::setPowerUps() {

}

void PurpleScene::setDoors() {

}

void PurpleScene::setObstacles() {


}
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
	return glm::ivec2(6, 6) * TILE_SIZE;
}

void GreenScene::setEnemies() {
	
}

void GreenScene::setPowerUps() {
	
}

void GreenScene::setDoors() {
	
}

void GreenScene::setObstacles() {

	
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "CollisionMap.h"
#include <windows.h>

using namespace std;

#define OFFSET glm::ivec2(0, -8)

CollisionMap *CollisionMap::createCollisionMap(const string &levelFile)
{
	CollisionMap *map = new CollisionMap(levelFile);
	
	return map;
}


CollisionMap::CollisionMap(const string &levelFile)
{
	loadLevel(levelFile);
}

CollisionMap::~CollisionMap()
{
	if(map != NULL)
		delete map;
}

void CollisionMap::setPlayerCollisonBox(const CollisionBox &collisionBox) {
	playerCollisionBox = playerCollisionBox;
}

bool CollisionMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 12, "COLLISIONMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize;
	
	map = new int[mapSize.x * mapSize.y];
	for(int j=0; j<mapSize.y; j++)
	{
		for(int i=0; i<mapSize.x; i++)
		{
			fin.get(tile);
			if(tile == ' ')
				map[j*mapSize.x+i] = 0;
			else
				map[j*mapSize.x+i] = tile - int('0');
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}

Tiles CollisionMap::getTiles(const CollisionBox &collisionBox) {
	Tiles tiles;
	tiles.min = glm::ivec2((collisionBox.min.x + OFFSET.x) / tileSize, (collisionBox.min.y + OFFSET.y) / tileSize);
	tiles.max = glm::ivec2((collisionBox.max.x + OFFSET.x) / tileSize, (collisionBox.max.y + OFFSET.y) / tileSize);
	return tiles;
}

bool CollisionMap::collisionWithPlayer(const CollisionBox &collisionBox) {
	return (playerCollisionBox.min.x < collisionBox.max.x) && (collisionBox.min.x < playerCollisionBox.max.x)
		&& (playerCollisionBox.min.y < collisionBox.max.y) && (collisionBox.min.y < playerCollisionBox.max.y);
}

bool CollisionMap::collision(const CollisionBox &collisionBox) {
    Tiles tiles = getTiles(collisionBox);

    for(int j = tiles.min.y; j <= tiles.max.y; ++j) 
        for(int i = tiles.min.x; i <= tiles.max.x; ++i) 
            if(map[j * mapSize.x + i] == BLOCK) return true;
    return false;
}

bool CollisionMap::onGround(const CollisionBox &collisionBox) {
    Tiles tiles = getTiles(collisionBox);
    int yBlock = (collisionBox.max.y + 1 + OFFSET.y) / tileSize;

	for(int i = tiles.min.x; i <= tiles.max.x; ++i) 
		if(map[yBlock * mapSize.x + i] == BLOCK) {
			for(int j = tiles.min.x; j <= tiles.max.x; ++j) 
				if(map[tiles.max.y * mapSize.x + j] == BLOCK) 
					return false;
			return true;
		}
    return false;
}

glm::ivec2 CollisionMap::onVine(const CollisionBox &collisionBox) {
    Tiles tiles = getTiles(collisionBox);

    for(int j = tiles.min.y; j <= tiles.max.y; ++j) 
        for(int i = tiles.min.x; i <= tiles.max.x; ++i) 
            if(map[j * mapSize.x + i] == VINE)
				return tileSize * glm::ivec2(i, j);
    return glm::ivec2(-1, -1);
}

glm::ivec2 CollisionMap::aboveVine(const CollisionBox &collisionBox) {
	Tiles tiles = getTiles(collisionBox);
	int y = (collisionBox.max.y + 1 + OFFSET.y) / tileSize;

	for(int i = tiles.min.x; i <= tiles.max.x; ++i) 
		if(map[y * mapSize.x + i] == VINE) 
			return tileSize * glm::ivec2(i, y);
    return glm::ivec2(-1, -1);
}
#include <iostream>
#include <fstream>
#include <sstream>
#include "CollisionMap.h"
#include <windows.h>


using namespace std;


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

bool CollisionMap::collision(const CollisionBox &collisionBox) {
    
    int xIni = collisionBox.min.x / tileSize; 
    int xEnd = collisionBox.max.x / tileSize;
    int yIni = collisionBox.min.y / tileSize;
    int yEnd = collisionBox.max.y / tileSize;

    for(int j = yIni; j <= yEnd; ++j) 
        for(int i = xIni; i <= xEnd; ++i) 
            if(map[j * mapSize.x + i] != 0) return true;
    return false;
}































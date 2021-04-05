#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.

class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const int &layer, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const int &layer, const glm::vec2 &minCoords, ShaderProgram &program);

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }
	int getLayer() const { return layer; }

private:
	int tileSize, blockSize, layer;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
};


#endif // _TILE_MAP_INCLUDE



#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define OFFSET_X 0
#define OFFSET_Y 0

#define INIT_PLAYER_X_TILES 6
#define INIT_PLAYER_Y_TILES 6


Scene::Scene()
{
	tileMap = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(tileMap != NULL)
		delete tileMap;
	if(player != NULL)
		delete player
}


void Scene::init()
{
	initShaders();

	tileMap = TileMap::createTileMap("levels/test.tm", glm::vec2(OFFSET_X, OFFSET_Y), texProgram);
	collisionMap = CollisionMap::createCollisionMap("levels/test.cm");

	player = new Player();
	player->init(glm::ivec2(OFFSET_X, OFFSET_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * tileMap->getTileSize(), INIT_PLAYER_Y_TILES * tileMap->getTileSize()));
	player->setCollisionMap(collisionMap);

	enemy = new Enemy();
	enemy->init(glm::ivec2(OFFSET_X, OFFSET_Y), texProgram);
	enemy->setPosition(glm::vec2(8 * 16, 7 * 16));
	enemy->setPatrolPoints(8 * 16, 14 * 16);
	enemy->setCollisionMap(collisionMap);

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	enemy->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	tileMap->render();
	player->render();
	enemy->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}




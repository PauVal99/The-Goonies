#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "PowerUp.h"
#include "Scene.h"


Scene::Scene()
{
	player = NULL;
}

Scene::~Scene()
{
	for(auto map : tileMaps)
		if (map.second)
			delete map.second;
	for(auto enemy : enemies)
		delete enemy;
}

void Scene::init()
{
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	setTileMaps();

	player = new Player();
	player->init(setPlayerPosition(), OFFSET, collisionMap, texProgram);

	hypershoes = new HyperShoes();
	hypershoes->init(glm::ivec2(10, 8) * TILE_SIZE, OFFSET, collisionMap, texProgram);

	setEnemies();

}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);

	hypershoes->update(deltaTime);
	
	for(auto enemy : enemies)
		enemy->update(deltaTime);

	for(auto enemy : enemies) {
		CollisionBox playerCollisionBox = player->getCollisionBox();
		if(collision(playerCollisionBox, enemy->getCollisionBox()))
			player->takeDamage(enemy->damage());
	}
}

bool Scene::collision(const CollisionBox &collisionBox1, const CollisionBox &collisionBox2) {
	return (collisionBox1.min.x < collisionBox2.max.x) && (collisionBox2.min.x < collisionBox1.max.x)
		&& (collisionBox1.min.y < collisionBox2.max.y) && (collisionBox2.min.y < collisionBox1.max.y);
}

void Scene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	
	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	for(auto map : tileMaps)
		map.second->render();
		
	player->render();
	hypershoes->render();

	for(auto enemy : enemies)
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




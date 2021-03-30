#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Scene.h"

Scene::Scene()
{
	player = NULL;
	camera = NULL;
}

Scene::~Scene()
{
	for(auto map : tileMaps)
		if (map.second)
			delete map.second;
	delete collisionMap;
	for(auto enemy : enemies)
		delete enemy;
	for(auto powerUp : powerUps)
		delete powerUp;
	for(auto door : doors)
		delete door;
	delete camera;

	tileMaps.clear();
	enemies.clear();
	powerUps.clear();
	doors.clear();
}

void Scene::init(Player* player)
{
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	setTileMaps();

	this->player = player;
	player->init(setPlayerPosition(), OFFSET, texProgram);
	player->setCollisionMap(collisionMap);

	setEnemies();
	setPowerUps();
	setDoors();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	updateActors(deltaTime);

	CollisionBox playerCollisionBox = player->getCollisionBox();

	for(unsigned int i = 0; i < enemies.size(); ++i) {
		if(!enemies[i]->isDead()) {
			if (player->isAttacking() && collision(player->getPunchCollisionBox(), enemies[i]->getCollisionBox())) 
				enemies[i]->die();
			else if(collision(playerCollisionBox, enemies[i]->getCollisionBox()))
				player->takeDamage(enemies[i]->damage());
		} else if (enemies[i]->remove()) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}

	for (unsigned int i = 0; i < powerUps.size(); ++i)
		if (collision(playerCollisionBox, powerUps[i]->getCollisionBox()))
			if(powerUps[i]->activatable(player)) {
				powerUps[i]->activatePowerUp(player);
				delete powerUps[i];
				powerUps.erase(powerUps.begin() + i);
			}

	for (auto door : doors)
		if (collision(playerCollisionBox, door->getCollisionBox()))
			if (door->playerInteraction(player->hasKey()))
				player->removeKey();			
}

void Scene::updateActors(int deltaTime) {
	player->update(deltaTime);
	camera->update(player->getPosition());

	if (!player->isTimePowerUpActive())
		for (auto enemy : enemies)
			enemy->update(deltaTime);

	for (auto powerUp : powerUps)
		powerUp->update(deltaTime);

	for (auto door : doors)
		door->update(deltaTime);
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
	
	glm::mat4 camView = glm::mat4(1.f);
	camView = glm::translate(camView, glm::vec3(camera->getTranslation(), 0.f));
	texProgram.setUniformMatrix4f("cameraView", camView);

	glm::mat4 modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	
	for(auto map : tileMaps)
		map.second->render();

	for(auto enemy : enemies)
		enemy->render();

	for (auto powerUp : powerUps)
		powerUp->render();

	for (auto door : doors) 
		door->render();

	player->render();
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
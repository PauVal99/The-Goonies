#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Scene.h"
#include "Skull.h"

Scene::Scene()
{
	player = NULL;
	camera = NULL;
	gui = NULL;
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


void Scene::createSkull(glm::ivec2 pos, glm::ivec2 patrolPoints) {

	Skull* skull = new Skull();
	skull->init(pos * TILE_SIZE, OFFSET, texProgram);
	skull->setCollisionMap(collisionMap);
	skull->setPatrolPoints(patrolPoints.x * TILE_SIZE, patrolPoints.y * TILE_SIZE);
	enemies.push_back(skull);
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

	gui = new GUI();
	gui->init(&texProgram);
	gui->setPlayer(player);

	setEnemies();
	setPowerUps();
	setDoors();
	setObstacles();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	updateActors(deltaTime);

	CollisionBox playerCollisionBox = player->getCollisionBox();

	for(auto enemy : enemies)
		if(!enemy->isDead()) {
			if (player->isAttacking() && collision(player->getPunchCollisionBox(), enemy->getCollisionBox())) {
				player->addExperience(enemy->experience());
				enemy->die();
			} else if(collision(playerCollisionBox, enemy->getCollisionBox()))
				player->takeDamage(enemy->damage());
		}

	for (auto powerUp : powerUps)
		if (!powerUp->isTaken() && powerUp->activatable(player) && collision(playerCollisionBox, powerUp->getCollisionBox()))
			powerUp->take(player);

	for (auto door : doors)
		if (collision(playerCollisionBox, door->getCollisionBox()) && door->playerInteraction(player->hasKey()))
			player->removeKey();

	for (auto obstacle : obstacles)
		if (collision(playerCollisionBox, obstacle->getCollisionBox()) && obstacle->hit())
			player->takeDamage(obstacle->damage());

	gui->update(deltaTime);		
}

void Scene::updateActors(int deltaTime) {
	player->update(deltaTime);
	camera->update(player->getPosition());

	for (unsigned int i = 0; i < enemies.size(); ++i) {
		if(!player->isTimePowerUpActive() || enemies[i]->isDead()) {
			enemies[i]->update(deltaTime);
			if(enemies[i]->remove()) {
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}
	}

	for (unsigned int i = 0; i < powerUps.size(); ++i) {
		powerUps[i]->update(deltaTime);
		if(powerUps[i]->remove()) {
			delete powerUps[i];
			powerUps.erase(powerUps.begin() + i);
		}
	}

	for (auto door : doors)
		door->update(deltaTime);

	for (auto obstacle : obstacles)
		obstacle->update(deltaTime);
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

	for (auto door : doors) 
		door->render();

	for (auto obstacle : obstacles)
		obstacle->render();

	for (auto powerUp : powerUps)
		powerUp->render();

	for(auto enemy : enemies)
		enemy->render();

	player->render();

	camView = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("cameraView", camView);
	gui->render();
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
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Scene.h"


#define MAX_TIME_COOLDOWN 10000

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
	delete camera;
	for(auto enemy : enemies)
		delete enemy;
}

void Scene::init()
{
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	setTileMaps();

	player = new Player();
	player->init(setPlayerPosition(), OFFSET, texProgram);
	player->setCollisionMap(collisionMap);

	setEnemies();
	setPowerUps();
}

void Scene::activateTimePowerUp(int deltaTime) {

	if (timeCooldown <= 0) {
		if (Game::instance().getKey('t') && player -> isTimePowerUpActivated()) {
			timeCooldown = MAX_TIME_COOLDOWN;
			player->deactivateTimePowerUp();
		}
	}
	else if (timeCooldown > 0)timeCooldown -= deltaTime;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;

	updateActors(deltaTime);

	activateTimePowerUp(deltaTime);

	CollisionBox playerCollisionBox = player->getCollisionBox();

	for(auto enemy : enemies)
		if(collision(playerCollisionBox, enemy->getCollisionBox()))
			player->takeDamage(enemy->damage());

	for (unsigned int i = 0; i < powerUps.size(); i++)
		if (collision(playerCollisionBox, powerUps[i]->getCollisionBox())) {
			powerUps[i]->activatePowerUp(player);
			delete powerUps[i];
			powerUps.erase(powerUps.begin() + i);
		}
}

void Scene::updateActors(int deltaTime) {
	player->update(deltaTime);
	camera->update(player->getPosition());

	if (timeCooldown <= 0) {
		for (auto enemy : enemies)
			enemy->update(deltaTime);
	}

	for (auto powerUp : powerUps)
		powerUp->update(deltaTime);
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
		
	player->render();

	for(auto enemy : enemies)
		enemy->render();

	for (auto powerUp : powerUps)
		powerUp->render();

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
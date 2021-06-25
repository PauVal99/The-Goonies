#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Start.h"

void Start::init(Player* player) {
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	startTexture = Texture();
	startTexture.loadFromFile("images/Start.png", TEXTURE_PIXEL_FORMAT_RGBA);
	startTexture.setMagFilter(GL_NEAREST);
	start = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(0.5f, 1.f), &startTexture, &texProgram);
	start->setPosition(glm::vec2(0.f));

	instructionsTexture = Texture();
	instructionsTexture.loadFromFile("images/Instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructionsTexture.setMagFilter(GL_NEAREST);
	instructions = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f), &instructionsTexture, &texProgram);
	instructions->setPosition(glm::vec2(0.f));

	start->setNumberAnimations(1);
	start->setAnimationSpeed(0, 2);
	start->addKeyframe(0, glm::vec2(0.f));
	start->addKeyframe(0, glm::vec2(0.5f, 0.f));
	start->changeAnimation(0);
}

void Start::update(int deltaTime) {
	currentTime += deltaTime;
	start->update(deltaTime);

	if(Game::instance().getKey(GLUT_KEY_SPACEBAR))
		cooldown -= deltaTime;

	if(cooldown < 5000) {
		cooldown -= deltaTime;
		if(cooldown <= 0)
			Game::instance().start();
	}
		
}

void Start::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("cameraView", glm::mat4(1.f));
	texProgram.setUniformMatrix4f("modelview", glm::mat4(1.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	if(cooldown == 5000)
		start->render();
	else
		instructions->render();
}
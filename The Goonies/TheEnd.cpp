#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "TheEnd.h"

void TheEnd::init(Player* player) {
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

    theEndTexture = Texture();
	theEndTexture.loadFromFile("images/TheEnd.png", TEXTURE_PIXEL_FORMAT_RGBA);
	theEndTexture.setMagFilter(GL_NEAREST);
	theEnd = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(0.5f, 1.f), &theEndTexture, &texProgram);
    theEnd->setPosition(glm::vec2(0.f));

	theEnd->setNumberAnimations(1);
	theEnd->setAnimationSpeed(0, 2);
	theEnd->addKeyframe(0, glm::vec2(0.f));
	theEnd->addKeyframe(0, glm::vec2(0.5f, 0.f));
    theEnd->changeAnimation(0);
}

void TheEnd::update(int deltaTime) {
    currentTime += deltaTime;
    theEnd->update(deltaTime);
}

void TheEnd::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("cameraView", glm::mat4(1.f));
	texProgram.setUniformMatrix4f("modelview", glm::mat4(1.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

    theEnd->render();
}
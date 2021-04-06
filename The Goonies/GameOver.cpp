#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "GameOver.h"

void GameOver::init(Player* player) {
	currentTime = 0.0f;
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

    gameOverTexture = Texture();
	gameOverTexture.loadFromFile("images/GameOver.png", TEXTURE_PIXEL_FORMAT_RGBA);
	gameOverTexture.setMagFilter(GL_NEAREST);
	gameOver = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f), &gameOverTexture, &texProgram);
    gameOver->setPosition(glm::vec2(0.f));
}

void GameOver::update(int deltaTime) {
    currentTime += deltaTime;
    gameOver->update(deltaTime);
}

void GameOver::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("cameraView", glm::mat4(1.f));
	texProgram.setUniformMatrix4f("modelview", glm::mat4(1.f));
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

    gameOver->render();
}
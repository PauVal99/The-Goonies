#include "HyperShoes.h"


void HyperShoes::init(const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram, const glm::ivec2& pos) {

	spritesheet.loadFromFile("images/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);

	sprite->setPosition(glm::vec2(float(tileMapOffset.x + pos.x), float(tileMapOffset.y + pos.y)));
}

void HyperShoes::activatePowerUp() {


}
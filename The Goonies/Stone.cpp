#include <GL/glew.h>
#include <GL/glut.h>
#include "Stone.h"
#include "Chain.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(32, 48)

#define DIE_TIME 0

enum StoneAnims
{
	RED, GREEN, PURPLE, YELLOW
};

void Stone::init(const glm::ivec2& iniPos, const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram)
{
	spritesheet = Texture();
	spritesheet.loadFromFile(setImage(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(setSize(), setSizeInSpritesheet(), &spritesheet, &shaderProgram);

	this->iniPos = iniPos;
	this->iniPos.y -= 8;
	setPosition(this->iniPos);
	setAnimations();
	this->tileMapOffset = tileMapOffset;
	setChains(shaderProgram);
}

void Stone::setChains(ShaderProgram& shaderProgram) {
	int posYCounter = iniPos.y + 32;
	for (int i = 0; i < 15; i++) {
		Chain* x = new Chain();
		x->init(glm::ivec2(iniPos.x, posYCounter), glm::ivec2(0, 0), shaderProgram);
		chains.push_back(x);
		renderChain.push_back(false);
		posYCounter += 16;
	}
	renderChain[0] = true;
	lastChainRendered = 0;
}

void Stone::render() {

	sprite->render();
	for (int i = 0; i < renderChain.size(); i++) {
		if (renderChain[i] == true)chains[i]->render();
	}
}

string Stone::setImage() {
	return "images/Obstacles/Stone.png";
}

glm::vec2 Stone::setSize() {
	return glm::vec2(32, 48);
}

glm::vec2 Stone::setSizeInSpritesheet() {
	return glm::vec2(0.25, 1);
}

CollisionBox Stone::setCollisionBox() {
	CollisionBox collisionBox;
	
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
		
	return collisionBox;
}

bool Stone::hit() {
	return true;
}

int Stone::damage() {
	return 0;
}

void Stone::setAnimations() {
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(RED, 1);
	sprite->addKeyframe(RED, glm::vec2(0.0f, 0.0f));

	sprite->setAnimationSpeed(GREEN, 1);
	sprite->addKeyframe(GREEN, glm::vec2(0.25f, 0.0f));

	sprite->setAnimationSpeed(PURPLE, 1);
	sprite->addKeyframe(PURPLE, glm::vec2(0.5f, 0.0f));

	sprite->setAnimationSpeed(YELLOW, 1);
	sprite->addKeyframe(YELLOW, glm::vec2(0.75f, 0.0f));

	sprite->changeAnimation(RED);

}

bool Stone::computeCooldown(int deltaTime) {

	animationCooldown -= deltaTime;
	if (animationCooldown <= 0)return true;
	else return false;
}

void Stone::childUpdate(int deltaTime) {
	if (animationCooldown <= 0) animationCooldown = 300;
	if (computeCooldown(deltaTime)) {
		if (goingDown) {
			position.y += 16;
			lastChainRendered++;
			renderChain[lastChainRendered] = true;

			if (collisionMap->collision(getCollisionBox())) {
				renderChain[lastChainRendered] = false;
				lastChainRendered--;
				position.y -= 16;
				goingDown = false;
			}
		}
		else {
			position.y -= 16;
			renderChain[lastChainRendered] = false;
			lastChainRendered--;

			if (position.y <= iniPos.y) {
				goingDown = true;
			}
		}
	}
}

void Stone::changeAnimation(int animation) {
	sprite->changeAnimation(animation);
}
#include <GL/glew.h>
#include <GL/glut.h>
#include "Stone.h"
#include "Chain.h"

#define COLLISION_BOX_MIN glm::ivec2(0, 0)
#define COLLISION_BOX_MAX glm::ivec2(32, 48)

#define DIE_TIME 0


void Stone::init(const glm::ivec2& iniPos, const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram)
{
	spritesheet = Texture();
	spritesheet.loadFromFile(setImage(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(setSize(), setSizeInSpritesheet(), &spritesheet, &shaderProgram);

	setPosition(iniPos);
	setAnimations();
	this->iniPos = iniPos;
	this->tileMapOffset = tileMapOffset;
	setChains(shaderProgram);
	//collisionMap->setStone(glm::ivec2(iniPos.x/16, iniPos.y/16));
}

void Stone::setChains(ShaderProgram& shaderProgram) {
	
	int posYCounter = iniPos.y - 16;
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
	return glm::vec2(1, 1);
}

CollisionBox Stone::setCollisionBox() {
	CollisionBox collisionBox;
	
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
		
	return collisionBox;
}

int Stone::damage() {
	return 0;
}

void Stone::setAnimations() {

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
				goingDown = false;
			}
			collisionMap->updateStone(glm::ivec2(position.x / 16, position.y / 16), goingDown);
		}
		else {
			position.y -= 16;
			renderChain[lastChainRendered] = false;
			lastChainRendered--;

			

			if (position.y <= iniPos.y) {
				goingDown = true;
			}
			collisionMap->updateStone(glm::ivec2(position.x / 16, position.y / 16), goingDown);
		}
	}
}

int Stone::getType() {
	return 3;
}

void Stone::changeAnimation(int animation) {
	sprite->changeAnimation(animation);
}

bool Stone::isRestarting() {
	return restarting;
}

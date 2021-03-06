#include <GL/glew.h>
#include <GL/glut.h>
#include "Actor.h"
#include "CollisionBox.h"

void Actor::init(const glm::ivec2 &iniPos, const glm::ivec2 &tileMapOffset, ShaderProgram &shaderProgram)
{
	this->tileMapOffset = tileMapOffset;
	spritesheet = Texture();
	spritesheet.loadFromFile(setImage(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(setSize(), setSizeInSpritesheet(), &spritesheet, &shaderProgram);

	setPosition(iniPos);
    setAnimations();
}

void Actor::setCollisionMap(CollisionMap* collisionMap) {
	this->collisionMap = collisionMap;
}

void Actor::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	if(!isEnded()) {
    	childUpdate(deltaTime);
		setPosition(position);
	} else {
		endTime -= deltaTime;
		if(endTime <= 0)
			removed = true;
	}
    
}

void Actor::render() {
	sprite->render();
}

void Actor::setPosition(const glm::ivec2& position)
{
	this->position = position;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + position.x), float(tileMapOffset.y + position.y)));
}

CollisionBox Actor::getCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = position + setCollisionBox().min;
	collisionBox.max = position + setCollisionBox().max;
	collisionBox.min += tileMapOffset;
	collisionBox.max += tileMapOffset;
	return collisionBox;
}

void Actor::setColor(const glm::vec4 &color) {
	sprite->setColor(color);
}

void Actor::resetColor() {
	sprite->setColor(glm::vec4(1.f));
}

void Actor::discard() {
	sprite->setColor(glm::vec4(0.f));
}

void Actor::end() {
	endTime = setEndTime();
	sprite->changeAnimation(setEndAnimation());
}

bool Actor::isEnded() {
	return endTime != 0;
}
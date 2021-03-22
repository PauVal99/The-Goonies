#include <GL/glew.h>
#include <GL/glut.h>
#include "Actor.h"

void Actor::init(const glm::ivec2 &iniPos, const glm::ivec2 &tileMapOffset, CollisionMap* collisionMap, ShaderProgram &shaderProgram)
{
	spritesheet.loadFromFile(setImage(), TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(setSize(), setSizeInSpritesheed(), &spritesheet, &shaderProgram);

    setAnimations();

	this->tileMapOffset = tileMapOffset;
    this->collisionMap = collisionMap;
    setPosition(iniPos);
}

void Actor::update(int deltaTime)
{
	sprite->update(deltaTime);
	
    childUpdate();

    setPosition(position);
}

void Actor::render()
{
	sprite->render();
}

void Actor::setPosition(const glm::ivec2& position)
{
	this->position = position;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + position.x), float(tileMapOffset.y + position.y)));
}
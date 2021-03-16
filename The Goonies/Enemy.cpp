#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"

#define MOVE_SPEED 1

enum EnemyAnims
{
	MOVE_LEFT, MOVE_RIGHT
};

void Enemy::init(const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Skull.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);

	sprite->setAnimationSpeed(MOVE_LEFT, 2);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.f));
	
	sprite->setAnimationSpeed(MOVE_RIGHT, 2);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(MOVE_RIGHT);
	this->tileMapOffset = tileMapOffset;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posEnemy.x), float(tileMapOffset.y + posEnemy.y)));
}

void Enemy::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	if (posEnemy.x <= patrolPoint1) movingRight = true;
	else if (posEnemy.x >= patrolPoint2) movingRight = false;

	if (movingRight) {
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posEnemy.x += MOVE_SPEED;
	}
	else {
		if (sprite->animation() != MOVE_LEFT) 
			sprite->changeAnimation(MOVE_LEFT);
		posEnemy.x -= MOVE_SPEED;
	}

	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posEnemy.x), float(tileMapOffset.y + posEnemy.y)));
}

void Enemy::render()
{
	sprite->render();
}

void Enemy::setCollisionMap(CollisionMap* collisionMap)
{
	map = collisionMap;
}

void Enemy::setPosition(const glm::ivec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posEnemy.x), float(tileMapOffset.y + posEnemy.y)));
}

void Enemy::setPatrolPoints(const int patrolPoint1, const int patrolPoint2) {
	this -> patrolPoint1 = patrolPoint1;
	this -> patrolPoint2 = patrolPoint2;
}
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_HEIGHT 48
#define JUMP_ANGLE_STEP 4
#define MOVE_SPEED 1
#define FALL_SPEED 4

#define COLLISION_BOX_MIN glm::ivec2(4, 0)
#define COLLISION_BOX_MAX glm::ivec2(26, 31)

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, CLIMB
};


void Player::init(const glm::ivec2 &tileMapOffset, ShaderProgram &shaderProgram)
{
	jumping = false;
	climbing = false;
	spritesheet.loadFromFile("images/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);

	setAnimations();

	this->tileMapOffset = tileMapOffset;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posPlayer.x), float(tileMapOffset.y + posPlayer.y)));
}

void Player::setAnimations() {
	sprite->setNumberAnimations(7);
	
	sprite->setAnimationSpeed(STAND_LEFT, 6);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.25f));
	
	sprite->setAnimationSpeed(STAND_RIGHT, 6);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
	
	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	
	sprite->setAnimationSpeed(MOVE_RIGHT, 6);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5, 0.f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(JUMP_LEFT, 6);
	sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.25f, 0.5f));
	
	sprite->setAnimationSpeed(JUMP_RIGHT, 6);
	sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(CLIMB, 6);
	sprite->addKeyframe(CLIMB, glm::vec2(0.f, 0.75f));
	sprite->addKeyframe(CLIMB, glm::vec2(0.25f, 0.75f));
		
	sprite->changeAnimation(STAND_RIGHT);
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	
	moveSideways();
	climb();
	jump();

	if(!jumping && !climbing && !map->onGround(getCollisionBox()))
		posPlayer.y += FALL_SPEED;

	map->setPlayerCollisonBox(getCollisionBox());
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posPlayer.x), float(tileMapOffset.y + posPlayer.y)));
}

void Player::moveSideways() {
	if(!climbing) {
		if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			posPlayer.x -= MOVE_SPEED;
			if(jumping)
				sprite->changeAnimation(JUMP_LEFT);
			else if(sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			
			if(map->collision(getCollisionBox())) {
				posPlayer.x += MOVE_SPEED;
				if(sprite->animation() == MOVE_LEFT)
					sprite->changeAnimation(STAND_LEFT);
			}
		} else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			posPlayer.x += MOVE_SPEED;
			if(jumping)
				sprite->changeAnimation(JUMP_RIGHT);
			else if(sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);

			if(map->collision(getCollisionBox())) {
				posPlayer.x -= MOVE_SPEED;
				if(sprite->animation() == MOVE_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
		} else {
			if(sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if(sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
}

void Player::climb() {
	bool onGround = map->onGround(getCollisionBox());
	glm::ivec2 onVine = map->onVine(getCollisionBox());
	glm::ivec2 aboveVine = map->aboveVine(getCollisionBox());

	if(climbing) {
		if (onGround || (onVine == glm::ivec2(-1, -1))) {
			climbing = false;
			sprite->changeAnimation(STAND_RIGHT);
		} else if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			sprite->startAnimation();
			posPlayer.y -= MOVE_SPEED;
		} else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			sprite->startAnimation();
			posPlayer.y += MOVE_SPEED;
		} else sprite->pauseAnimation();
	} else if(onGround && (onVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		climbing = true;
		sprite->changeAnimation(CLIMB);
		posPlayer.x = onVine.x - 6;
		posPlayer.y -= MOVE_SPEED;
	} else if((aboveVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		climbing = true;
		sprite->changeAnimation(CLIMB);
		posPlayer.x = aboveVine.x - 6;
		posPlayer.y = aboveVine.y;
		posPlayer.y += MOVE_SPEED;
	}
}

void Player::jump() {
	if(jumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) {
			jumping = false;
			posPlayer.y = startY;
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else if(map->collision(getCollisionBox())) {
			jumping = false;
			if(jumpAngle > 90) posPlayer.y = (posPlayer.y / map->getTileSize()) * map->getTileSize();
			else posPlayer.y = (posPlayer.y / map->getTileSize() + 1) * map->getTileSize();
			
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	} else if(!climbing && Game::instance().getSpecialKey(GLUT_KEY_UP) && map->onGround(getCollisionBox())) {
		if((sprite->animation() == MOVE_LEFT) || (sprite->animation() == STAND_LEFT))
			sprite->changeAnimation(JUMP_LEFT);
		else sprite->changeAnimation(JUMP_RIGHT);
		
		jumping = true;
		jumpAngle = 0;
		startY = posPlayer.y;
	}
}

CollisionBox Player::getCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = posPlayer + COLLISION_BOX_MIN;
	collisionBox.max = posPlayer + COLLISION_BOX_MAX;
	collisionBox.min += tileMapOffset;
	collisionBox.max += tileMapOffset;
	return collisionBox;
}

void Player::render()
{
	sprite->render();
}

void Player::setCollisionMap(CollisionMap *collisionMap)
{
	map = collisionMap;
}

void Player::setPosition(const glm::ivec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posPlayer.x), float(tileMapOffset.y + posPlayer.y)));
}
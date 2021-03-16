#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_HEIGHT 48
#define MOVE_SPEED 1
#define FALL_SPEED 4

#define JUMP_ANGLE_STEP 4

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT 
};


void Player::init(const glm::ivec2 &tileMapOffset, ShaderProgram &shaderProgram)
{
	jumping = false;
	spritesheet.loadFromFile("images/Player.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
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
		
	sprite->changeAnimation(STAND_RIGHT);
	this->tileMapOffset = tileMapOffset;
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posPlayer.x), float(tileMapOffset.y + posPlayer.y)));
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
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
	
	if(jumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) {
			jumping = false;
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else if ((jumpAngle > 90) && map->collision(getCollisionBox())) {
			jumping = false;
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	} else {
		posPlayer.y += FALL_SPEED;
		if(map->collision(getCollisionBox())) {
			posPlayer.y -= FALL_SPEED;
			if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				if((sprite->animation() == MOVE_LEFT) || (sprite->animation() == STAND_LEFT))
					sprite->changeAnimation(JUMP_LEFT);
				else sprite->changeAnimation(JUMP_RIGHT);
				
				jumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}
	
	map->setPlayerCollisonBox(getCollisionBox());
	sprite->setPosition(glm::vec2(float(tileMapOffset.x + posPlayer.x), float(tileMapOffset.y + posPlayer.y)));
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

CollisionBox Player::getCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min.x = posPlayer.x + 6;
	collisionBox.min.y = posPlayer.y + 2;
	collisionBox.max.x = posPlayer.x + 26;
	collisionBox.max.y = posPlayer.y + 30;
	return collisionBox;
}
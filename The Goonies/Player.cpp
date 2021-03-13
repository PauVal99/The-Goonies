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

const glm::ivec2 playerSize = glm::ivec2(32, 32);

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT 
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
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
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
		if(jumping)
			sprite->changeAnimation(JUMP_LEFT);
		else if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		
		if(map->collisionMoveLeft(posPlayer, playerSize)) {
			posPlayer.x += MOVE_SPEED;
			if(sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
		}
		posPlayer.x -= MOVE_SPEED;
	} else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
		if(jumping)
			sprite->changeAnimation(JUMP_RIGHT);
		else if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);

		if(map->collisionMoveRight(posPlayer, playerSize)) {
			posPlayer.x -= MOVE_SPEED;
			if(sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
		posPlayer.x += MOVE_SPEED;
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
		} else if ((jumpAngle > 90) && map->collisionMoveDown(posPlayer, playerSize)) {
			jumping = false;
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	} else {
		posPlayer.y += FALL_SPEED;
		if(map->collisionMoveDown(posPlayer, playerSize)) {
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
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}
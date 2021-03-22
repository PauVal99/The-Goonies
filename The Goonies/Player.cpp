#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Player.h"

#define JUMP_HEIGHT 48
#define JUMP_ANGLE_STEP 4
#define MOVE_SPEED 1
#define FALL_SPEED 4

#define COLLISION_BOX_MIN glm::ivec2(4, 0)
#define COLLISION_BOX_MAX glm::ivec2(25, 31)

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, CLIMB
};

string Player::setImage() {
	return "images/Player.png";
}

glm::vec2 Player::setSize() {
	return glm::ivec2(32, 32);
}

glm::vec2 Player::setSizeInSpritesheed() {
	return glm::vec2(0.25, 0.25);
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

void Player::childUpdate()
{	
	moveSideways();
	climb();
	jump();

	if(!jumping && !climbing && !collisionMap->onGround(getCollisionBox()))
		position.y += FALL_SPEED;

	collisionMap->setPlayerCollisonBox(getCollisionBox());
}

void Player::moveSideways() {
	if(!climbing) {
		if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			position.x -= MOVE_SPEED;
			if(jumping)
				sprite->changeAnimation(JUMP_LEFT);
			else if(sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			
			if(collisionMap->collision(getCollisionBox())) {
				position.x += MOVE_SPEED;
				if(sprite->animation() == MOVE_LEFT)
					sprite->changeAnimation(STAND_LEFT);
			}
		} else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			position.x += MOVE_SPEED;
			if(jumping)
				sprite->changeAnimation(JUMP_RIGHT);
			else if(sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);

			if(collisionMap->collision(getCollisionBox())) {
				position.x -= MOVE_SPEED;
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
	bool onGround = collisionMap->onGround(getCollisionBox());
	glm::ivec2 onVine = collisionMap->onVine(getCollisionBox());
	glm::ivec2 aboveVine = collisionMap->aboveVine(getCollisionBox());

	if(climbing) {
		if (onGround || (onVine == glm::ivec2(-1, -1))) {
			climbing = false;
			sprite->changeAnimation(STAND_RIGHT);
		} else if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			sprite->startAnimation();
			position.y -= MOVE_SPEED;
		} else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			sprite->startAnimation();
			position.y += MOVE_SPEED;
		} else sprite->pauseAnimation();
	} else if(onGround && (onVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
		climbing = true;
		sprite->changeAnimation(CLIMB);
		position.x = onVine.x - 6;
		position.y -= MOVE_SPEED;
	} else if((aboveVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
		climbing = true;
		sprite->changeAnimation(CLIMB);
		position.x = aboveVine.x - 6;
		position.y = aboveVine.y;
		position.y += MOVE_SPEED;
	}
}

void Player::jump() {
	if(jumping) {
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180) {
			jumping = false;
			position.y = startY;
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else if(collisionMap->collision(getCollisionBox())) {
			jumping = false;
			if(jumpAngle > 90) position.y = (position.y / collisionMap->getTileSize()) * collisionMap->getTileSize();
			else position.y = (position.y / collisionMap->getTileSize() + 1) * collisionMap->getTileSize();
			
			if(sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else sprite->changeAnimation(STAND_RIGHT);
		} else
			position.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	} else if(!climbing && Game::instance().getSpecialKey(GLUT_KEY_UP) && collisionMap->onGround(getCollisionBox())) {
		if((sprite->animation() == MOVE_LEFT) || (sprite->animation() == STAND_LEFT))
			sprite->changeAnimation(JUMP_LEFT);
		else sprite->changeAnimation(JUMP_RIGHT);
		
		jumping = true;
		jumpAngle = 0;
		startY = position.y;
	}
}

CollisionBox Player::getCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = position + COLLISION_BOX_MIN;
	collisionBox.max = position + COLLISION_BOX_MAX;
	collisionBox.min += tileMapOffset;
	collisionBox.max += tileMapOffset;
	return collisionBox;
}
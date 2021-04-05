#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Player.h"

#define JUMP_HEIGHT 32
#define JUMP_ANGLE_STEP 4
#define FALL_SPEED 4

#define COLLISION_BOX_MIN glm::ivec2(4, 0)
#define COLLISION_BOX_MAX glm::ivec2(25, 31)

#define PUNCH_COLLISION_BOX_MIN_RIGHT glm::ivec2(24, 6)
#define PUNCH_COLLISION_BOX_MAX_RIGHT glm::ivec2(36, 18)

#define PUNCH_COLLISION_BOX_MIN_LEFT glm::ivec2(-4, 6)
#define PUNCH_COLLISION_BOX_MAX_LEFT glm::ivec2(8, 18)

#define DAMAGE_COOLDOWN 2000
#define DAMAGE_COLOR glm::vec4(1.4f, 1.4f, 1.4f, 1.f)

#define HEALTH_INCREMENT 20
#define SHIELD_HITS 3

#define MAX_EXPERIENCE 100
#define EXPERIENCE_POTION 60

#define TIME_POWER_UP_COOLDOWN 10000

#define ATTACK_DURATION 300

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, CLIMB, PUNCH_RIGHT, PUNCH_LEFT
};

string Player::setImage() {
	return "images/Player.png";
}

glm::vec2 Player::setSize() {
	return glm::vec2(32, 32);
}

glm::vec2 Player::setSizeInSpritesheet() {
	return glm::vec2(0.25, 0.25);
}

void Player::takeDamage(const int &damage) {
	if(damageCooldown == 0) {
		if(shieldHitsCounter == 0) {
			health -= damage;
			if(health <= 0)
				Game::instance().restart();
		} else --shieldHitsCounter;
		damageCooldown = DAMAGE_COOLDOWN;
	}
}

void Player::addExperience(int exp) {
	experience += exp;
	if (experience >= MAX_EXPERIENCE) {
		incrementMaxHealth();
		experience -= MAX_EXPERIENCE;
	}
}

void Player::incrementMaxHealth() {
	maxHealth += HEALTH_INCREMENT;
	health += HEALTH_INCREMENT;
}

void Player::activateHyperShoes() {
	moveSpeed = 2;
}

void Player::activateShield() {
	shieldHitsCounter = SHIELD_HITS;
}

void Player::activateVitalityPotion() {
	health = maxHealth;
}

void Player::activateExperiencePotion() {
	addExperience(EXPERIENCE_POTION);
}

bool Player::isTimePowerUpActive() {
	return timePoweUpCooldown > 0;
}

void Player::activateTimePowerUp() {
	timePowerUp = true;
}

void Player::addKey() {
	key = true;
}

bool Player::hasKey() {
	return key;
}

void Player::removeKey() {
	key = false;
}

bool Player::isAttacking() {
	return attacking > 0;
}

CollisionBox Player::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

CollisionBox Player::getPunchCollisionBox() {
	CollisionBox collisionBox;


	if(sprite->animation() == PUNCH_RIGHT) {
		collisionBox.min = position + PUNCH_COLLISION_BOX_MIN_RIGHT;
		collisionBox.max = position + PUNCH_COLLISION_BOX_MAX_RIGHT;
	} else {
		collisionBox.min = position + PUNCH_COLLISION_BOX_MIN_LEFT;
		collisionBox.max = position + PUNCH_COLLISION_BOX_MAX_LEFT;
	}

	collisionBox.min += tileMapOffset;
	collisionBox.max += tileMapOffset;
	return collisionBox;
}

void Player::setAnimations() {
	sprite->setNumberAnimations(9);
	
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

	sprite->setAnimationSpeed(PUNCH_RIGHT, 6);
	sprite->addKeyframe(PUNCH_RIGHT, glm::vec2(0.75f, 0.f));

	sprite->setAnimationSpeed(PUNCH_LEFT, 6);
	sprite->addKeyframe(PUNCH_LEFT, glm::vec2(0.75f, 0.25f));
		
	sprite->changeAnimation(STAND_RIGHT);
}

void Player::childUpdate(int deltaTime) {	
	attack(deltaTime);
	moveSideways();
	climb();
	jump();

	if(!jumping && !climbing && !collisionMap->onGround(getCollisionBox()))
		position.y += FALL_SPEED;

	if(Game::instance().getSpecialKey(GLUT_KEY_UP) && collisionMap->onPortal(getCollisionBox()))
		Game::instance().nextScene();

	timePowerUpUpdate(deltaTime);
	wounded(deltaTime);
}

void Player::attack(int deltaTime) {
	if(!jumping && !climbing && !isAttacking() && !prevSpace && Game::instance().getKey(GLUT_KEY_SPACEBAR)) {
		attacking = ATTACK_DURATION;
		if(sprite->animation() == STAND_RIGHT || sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(PUNCH_RIGHT);
		else
			sprite->changeAnimation(PUNCH_LEFT);
	}

	if(isAttacking()) {
		attacking -= deltaTime;
		if(attacking < 0)
			attacking = 0;
	}

	prevSpace = Game::instance().getKey(GLUT_KEY_SPACEBAR);
}

void Player::moveSideways() {
	if(!climbing && !isAttacking()) {
		if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			position.x -= moveSpeed;
			if(jumping)
				sprite->changeAnimation(JUMP_LEFT);
			else if(sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			
			if(collisionMap->collision(getCollisionBox())) {
				position.x += moveSpeed;
				if(sprite->animation() == MOVE_LEFT)
					sprite->changeAnimation(STAND_LEFT);
			}
		} else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			position.x += moveSpeed;
			if(jumping)
				sprite->changeAnimation(JUMP_RIGHT);
			else if(sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);

			if(collisionMap->collision(getCollisionBox())) {

				#include <windows.h>

				char buffer[100];
				sprintf_s(buffer, "hello\n");
				OutputDebugStringA(buffer);

				position.x -= moveSpeed;
				if(sprite->animation() == MOVE_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}
		} else {
			if(sprite->animation() == MOVE_LEFT || sprite->animation() == PUNCH_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if(sprite->animation() == MOVE_RIGHT || sprite->animation() == PUNCH_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
}

void Player::climb() {
	bool onGround = collisionMap->onGround(getCollisionBox());
	glm::ivec2 onVine = collisionMap->onVine(getCollisionBox());
	glm::ivec2 aboveVine = collisionMap->aboveVine(getCollisionBox());

	if(!jumping && !isAttacking()) {
		if(climbing) {
			if (onGround || (onVine == glm::ivec2(-1, -1))) {
				climbing = false;
				sprite->changeAnimation(STAND_RIGHT);
			} else if(Game::instance().getSpecialKey(GLUT_KEY_UP)) {
				sprite->startAnimation();
				position.y -= moveSpeed;
			} else if(Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
				sprite->startAnimation();
				position.y += moveSpeed;
			} else sprite->pauseAnimation();
		} else if(onGround && (onVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_UP)) {
			climbing = true;
			sprite->changeAnimation(CLIMB);
			position.x = onVine.x - 6;
			position.y -= moveSpeed;
		} else if((aboveVine != glm::ivec2(-1, -1)) && Game::instance().getSpecialKey(GLUT_KEY_DOWN)) {
			climbing = true;
			sprite->changeAnimation(CLIMB);
			position.x = aboveVine.x - 6;
			position.y = aboveVine.y;
			position.y += moveSpeed;
		}
	}
}

void Player::jump() {
	if(!climbing && !isAttacking()) {
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
		} else if(!prevUp && Game::instance().getSpecialKey(GLUT_KEY_UP) && collisionMap->onGround(getCollisionBox())) {
			if((sprite->animation() == MOVE_LEFT) || (sprite->animation() == STAND_LEFT))
				sprite->changeAnimation(JUMP_LEFT);
			else sprite->changeAnimation(JUMP_RIGHT);
			
			jumping = true;
			jumpAngle = 0;
			startY = position.y;
		}
	}

	prevUp = Game::instance().getSpecialKey(GLUT_KEY_UP);
}

void Player::wounded(int deltaTime) {
	damageCooldown -= deltaTime;
	
	if(damageCooldown > 0) {
		if((damageCooldown/(deltaTime * 2)) % 4 == 0)
			discard();
		else setColor(DAMAGE_COLOR);
	} else {
		damageCooldown = 0;
		resetColor();
	}
}

void Player::timePowerUpUpdate(int deltaTime) {
	if (timePowerUp && Game::instance().getKey('t')) {
		timePoweUpCooldown = TIME_POWER_UP_COOLDOWN;
		timePowerUp = false;
	}

	if (timePoweUpCooldown > 0)
		timePoweUpCooldown -= deltaTime;
}
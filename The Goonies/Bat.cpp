#include <GL/glew.h>
#include <GL/glut.h>
#include <random>
#include "Bat.h"

#define MOVE_SPEED 2

#define COLLISION_BOX_MIN glm::ivec2(2, 0)
#define COLLISION_BOX_MAX glm::ivec2(16, 13)

#define DAMAGE 20
#define EXPERIENCE 10

#define DIE_TIME 500

enum BatAnims
{
	MOVE, DIE
};	

string Bat::setImage() {
	return "images/Bat.png";
}

glm::vec2 Bat::setSize() {
	return glm::vec2(16, 16);
}

glm::vec2 Bat::setSizeInSpritesheet() {
	return glm::vec2(0.5f, 0.5f);
}

CollisionBox Bat::setCollisionBox() {
	CollisionBox collisionBox;
	collisionBox.min = COLLISION_BOX_MIN;
	collisionBox.max = COLLISION_BOX_MAX;
	return collisionBox;
}

void Bat::setAnimations() {
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE, 2);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(DIE, 4);
	sprite->addKeyframe(DIE, glm::vec2(0.f, 0.5f));
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.5f));

	sprite->changeAnimation(MOVE);
}

int Bat::setEndTime() {
	return DIE_TIME;
}

int Bat::setEndAnimation() {
	return DIE;
}

int Bat::damage() { 
	return DAMAGE;
}

int Bat::experience() {
    return EXPERIENCE;
}

void Bat::setPlayer(Player* player) {
    this->player = player;
}

void Bat::childUpdate(int deltaTime) {
    randomUpdateCooldown -= deltaTime;
    if(randomUpdateCooldown <= 0) {
        randomUpdateCooldown = 250;

        std::random_device rd;
        std::default_random_engine gen(rd());
        std::uniform_real_distribution<float> dis(-100.f, 100.f);
        random = glm::vec2(dis(rd), dis(rd));
    }

    float distance = glm::distance(glm::vec2(player->getPosition() + 6), glm::vec2(position));
    if(distance != 0 && distance <= 300) {
        glm::vec2 direction = glm::mix(glm::vec2(player->getPosition() + 6 - position), random, 0.5f);
        prevDirection = direction;
        direction = glm::mix(direction, prevDirection, 0.4f);
        position += float(MOVE_SPEED) * glm::normalize(direction);
        if(collisionMap->collision(getCollisionBox())) {
            position -= float(MOVE_SPEED) * glm::normalize(direction);
            randomUpdateCooldown = 0;
        }
    }
}
#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE

#include "Enemy.h"

class Skull: public Enemy
{

public:
	void setPatrolPoints(const int patrolPoint1, const int patrolPoint2);
    void die();
    int damage();
    bool isDead();
    bool remove();

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);

private:
	int patrolPoint1, patrolPoint2, dieTime = 0;
	bool movingRight = true, removed = false;

};

#endif
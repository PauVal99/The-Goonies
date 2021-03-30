#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE

#include "Enemy.h"

class Skull: public Enemy
{

public:
	void setPatrolPoints(const int patrolPoint1, const int patrolPoint2);
    int damage();

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);
    int setEndTime();
    int setEndAnimation();

private:
	int patrolPoint1, patrolPoint2;
	bool movingRight = true;

};

#endif
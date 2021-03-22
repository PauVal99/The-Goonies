#ifndef _SKULL_INCLUDE
#define _SKULL_INCLUDE

#include "Enemy.h"

class Skull: public Enemy
{

public:
	void setPatrolPoints(const int patrolPoint1, const int patrolPoint2);

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheed();
    void setAnimations();
    void childUpdate();

private:
	int patrolPoint1, patrolPoint2;
	bool movingRight = true;

};

#endif
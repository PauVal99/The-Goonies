#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Actor.h"
#include "Sprite.h"
#include "CollisionMap.h"

class Skull: public Actor
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



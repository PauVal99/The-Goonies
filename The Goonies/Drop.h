#ifndef _DROP_INCLUDE
#define _DROP_INCLUDE

#include "Obstacle.h"

class Drop : public Obstacle
{

public:
    int damage();
    int getType();
    void changeAnimation(int animation);
    bool isRestarting();

protected:
    string setImage();
    void render();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);
    int setEndTime();
    int setEndAnimation();

private:
    bool computeCooldown(int deltaTime);

private:
    int animationCooldown = 0;
    bool restarting = false;
    glm::vec2 iniPos;
};

#endif
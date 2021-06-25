#ifndef _VALVEWATER_INCLUDE
#define _VALVEWATER_INCLUDE

#include "Obstacle.h"

class ValveWater : public Obstacle
{

public:
    void setOrientation(int orientation);
    int damage();
    bool hit();

protected:
    string setImage();
    void render();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);
 

private:
    bool computeCooldown(int deltaTime);

private:
    int animationCooldown = 0;
    bool restarting = false;
    glm::vec2 iniPos;
    int orientation;
};

#endif
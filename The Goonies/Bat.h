#ifndef _BAT_INCLUDE
#define _BAT_INCLUDE

#include "Enemy.h"
#include "Player.h"

class Bat: public Enemy
{

public:
    int damage();
    void setPlayer(Player* playe);

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
    glm::ivec2 normalize(glm::ivec2 vec);

private:
    int randomUpdateCooldown;
    Player* player;
    glm::vec2 random;
    glm::vec2 prevDirection = glm::vec2(1,1);

};

#endif
#ifndef _STONE_INCLUDE
#define _STONE_INCLUDE

#include "Obstacle.h"
#include "Chain.h"

class Stone : public Obstacle
{

public:
    void init(const glm::ivec2& iniPos, const glm::ivec2& tileMapOffset, ShaderProgram& shaderProgram);
    void render();
    int damage();
    bool hit();
    void changeAnimation(int animation);

protected: 
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();
    void childUpdate(int deltaTime);
    void setChains(ShaderProgram& shaderProgram);

private:
    bool computeCooldown(int deltaTime);

private:
    int animationCooldown = 0;
    bool restarting = false;
    glm::ivec2 iniPos;
    std::vector<Chain*> chains;
    std::vector<bool>renderChain;
    int lastChainRendered;
    bool goingDown = true;
};

#endif
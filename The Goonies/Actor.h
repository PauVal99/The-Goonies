#ifndef _ACTOR_INCLUDE
#define _ACTOR_INCLUDE

#include "Sprite.h"
#include "CollisionMap.h"

class Actor
{

public:
	void init(const glm::ivec2 &iniPos, const glm::ivec2 &tileMapOffset, CollisionMap* collisionMap, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::ivec2& pos);

protected:
    virtual string setImage() = 0;
    virtual glm::vec2 setSize() = 0;
    virtual glm::vec2 setSizeInSpritesheed() = 0;
    virtual void setAnimations() = 0;
    virtual void childUpdate() = 0;

protected:
    CollisionMap* collisionMap;
    glm::ivec2 position, tileMapOffset;
    Sprite* sprite;

private:
	Texture spritesheet;
};

#endif



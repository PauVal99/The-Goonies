#ifndef _ACTOR_INCLUDE
#define _ACTOR_INCLUDE

#include "Sprite.h"
#include "CollisionMap.h"
#include "CollisionBox.h"

class Actor
{

public:
	void init(const glm::ivec2 &iniPos, const glm::ivec2 &tileMapOffset, ShaderProgram &shaderProgram);
    void setCollisionMap(CollisionMap* collisionMap);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::ivec2& pos);
    CollisionBox getCollisionBox();

    inline glm::ivec2 getPosition() const { return position; };

protected:
    void setColor(const glm::vec4 &color);
    void resetColor();
    void discard();
    virtual string setImage() = 0;
    virtual glm::vec2 setSize() = 0;
    virtual glm::vec2 setSizeInSpritesheet() = 0;
    virtual CollisionBox setCollisionBox() = 0;
    virtual void setAnimations() {}
    virtual void childUpdate(int deltaTime) {}
   
protected:
    CollisionMap* collisionMap;
    glm::ivec2 position, tileMapOffset;
    Sprite* sprite;

private:
	Texture spritesheet;
};

#endif



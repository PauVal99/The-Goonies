#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Actor.h"

class Door: public Actor
{

public:
    bool playerInteraction(bool hasKey);
protected:
    virtual string setImage();
    virtual glm::vec2 setSize();
    virtual glm::vec2 setSizeInSpritesheet();
    virtual CollisionBox setCollisionBox();
    virtual void setAnimations();
    virtual void childUpdate(int deltaTime);

protected:
    

private:
 
    bool itemCollected = false;
    bool open = false;
};

#endif

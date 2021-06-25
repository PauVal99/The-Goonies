#ifndef _DOOR_INCLUDE
#define _DOOR_INCLUDE

#include "Actor.h"

class Door: public Actor
{

public:
    bool playerInteraction(bool hasKey);
    void setNumberOfKeys(int numKeys);
    void rescueFriend();
    bool isRescued() { return itemCollected; };

protected:
    string setImage();
    glm::vec2 setSize();
    glm::vec2 setSizeInSpritesheet();
    CollisionBox setCollisionBox();
    void setAnimations();

protected:
  

private:
    bool itemCollected = false;
    bool open = false;
    int numberOfKeys = 0;
};

#endif

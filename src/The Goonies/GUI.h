#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE

#include "Sprite.h"
#include "Player.h"

class GUI
{

public:
	void init(ShaderProgram *shaderProgram, int friendsToSave, int* savedFriends);
    void setPlayer(Player* player);
	void update(int deltaTime);
	void render();

private:
    void setSprite(Sprite* sprite, glm::vec2 displacement);
   
private:
    int friendsToSave;
    int* savedFriends;
    
    Player* player;
	Texture spritesheet, barTexture, clockTexture, bootsTexture;

    Sprite* health;
    Sprite* experience;
    Sprite* bar;
    Sprite* voidShield;
    Sprite* shield;
    Sprite* voidKey;
    Sprite* key;
    Sprite* voidFriend;
    Sprite* savedFriend;
    Sprite* clock;
    Sprite* boots;
    Sprite* marginTop;
    Sprite* marginBot;
    Sprite* godMode;
};
#endif
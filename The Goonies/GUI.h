#ifndef _GUI_INCLUDE
#define _GUI_INCLUDE

#include "Sprite.h"
#include "Player.h"

class GUI
{

public:
	void init(ShaderProgram *shaderProgram);
    void setPlayer(Player* player);
	void update(int deltaTime);
	void render();

private:
    void setSprite(Sprite* sprite, glm::vec2 displacement);
   
private:
    Player* player;
	Texture spritesheet, barTexture, clockTexture;

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

};
#endif
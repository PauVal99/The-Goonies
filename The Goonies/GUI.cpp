#include "GUI.h"

void GUI::init(ShaderProgram *shaderProgram)
{
	barTexture = Texture();
	barTexture.loadFromFile("images/bar.png", TEXTURE_PIXEL_FORMAT_RGBA);
	barTexture.setMagFilter(GL_NEAREST);

	bar = Sprite::createSprite(glm::vec2(128, 16), glm::vec2(1.f, 0.5f), &barTexture, shaderProgram);
	marginTop = Sprite::createSprite(glm::vec2(512, 44), glm::vec2(1.f, 0.5f), &barTexture, shaderProgram);
	setSprite(marginTop, glm::vec2(0, 0.5f));
	marginTop->setPosition(glm::vec2(0, 0));
	marginBot = Sprite::createSprite(glm::vec2(512, 24), glm::vec2(1.f, 0.5f), &barTexture, shaderProgram);
	setSprite(marginBot, glm::vec2(0, 0.5f));
	marginBot->setPosition(glm::vec2(0, 364));

	clockTexture = Texture();
	clockTexture.loadFromFile("images/PowerUps/Clock.png", TEXTURE_PIXEL_FORMAT_RGBA);
	clockTexture.setMagFilter(GL_NEAREST);

	clock = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 1.f), &clockTexture, shaderProgram);
	clock->setPosition(glm::vec2(400, 6));

	bootsTexture = Texture();
	bootsTexture.loadFromFile("images/PowerUps/HyperShoes.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bootsTexture.setMagFilter(GL_NEAREST);

	boots = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 1.f), &bootsTexture, shaderProgram);
	boots->setPosition(glm::vec2(436, 6));

	spritesheet = Texture();
	spritesheet.loadFromFile("images/GUI.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);

	health = Sprite::createSprite(glm::vec2(124, 16), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
	health->setPosition(glm::vec2(6, 4));

	experience = Sprite::createSprite(glm::vec2(0, 16), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
	setSprite(experience, glm::vec2(0, 0.5f));
	experience->setPosition(glm::vec2(6, 24));

	voidShield = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(voidShield, glm::vec2(0.5f, 0.5f));

	shield = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(shield, glm::vec2(0.5f, 0.f));

	voidKey = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(voidKey, glm::vec2(0.75f, 0.5f));
	voidKey->setPosition(glm::vec2(472, 6));

	key = Sprite::createSprite(glm::vec2(32, 32), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(key, glm::vec2(0.75f, 0.f));
	key->setPosition(glm::vec2(472, 6));

	voidFriend = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(voidFriend, glm::vec2(0.25f, 0.5f));

	savedFriend = Sprite::createSprite(glm::vec2(16, 16), glm::vec2(0.25f, 0.5f), &spritesheet, shaderProgram);
    setSprite(savedFriend, glm::vec2(0.25f, 0.f));
}

void GUI::setPlayer(Player* player) {
	this->player = player;
}

void GUI::update(int deltaTime) {
	health->setSize(glm::vec2((player->getHealth() * 124) / 100, 16));
	experience->setSize(glm::vec2((player->getExperience() * 124) / 100, 16));
}

void GUI::render() {
	marginTop->render();
	marginBot->render();
	health->render();
	experience->render();
	
	bar->setPosition(glm::vec2(4, 4));
	bar->render();
	bar->setPosition(glm::vec2(4, 24));
	bar->render();
	
	voidShield->setPosition(glm::vec2(136, 6));
	voidShield->render();
	voidShield->setPosition(glm::vec2(166, 6));
	voidShield->render();
	voidShield->setPosition(glm::vec2(196, 6));
	voidShield->render();

	if(player->getArmour() > 0) {
		shield->setPosition(glm::vec2(136, 6));
		shield->render();
		if(player->getArmour() > 1) {
			shield->setPosition(glm::vec2(166, 6));
			shield->render();
			if(player->getArmour() > 2) {
				shield->setPosition(glm::vec2(196, 6));
				shield->render();
			}
		}
	}

	if(player->hasKey())
		key->render();
	else
		voidKey->render();

	int savedFriends = player->getSavedFirends();

	if(savedFriends < 6) {
		voidFriend->setPosition(glm::vec2(104, 368));
		voidFriend->render();
		if(savedFriends < 5) {
			voidFriend->setPosition(glm::vec2(84, 368));
			voidFriend->render();
			if(savedFriends < 4) {
				voidFriend->setPosition(glm::vec2(64, 368));
				voidFriend->render();
				if(savedFriends < 3) {
					voidFriend->setPosition(glm::vec2(44, 368));
					voidFriend->render();
					if(savedFriends < 2) {
						voidFriend->setPosition(glm::vec2(24, 368));
						voidFriend->render();
						if(savedFriends < 1) {
							voidFriend->setPosition(glm::vec2(4, 368));
							voidFriend->render();
						}
					}
				}
			}
		}
	}

	if(savedFriends > 0) {
		savedFriend->setPosition(glm::vec2(4, 368));
		savedFriend->render();
		if(savedFriends > 1) {
			savedFriend->setPosition(glm::vec2(24, 368));
			savedFriend->render();
			if(savedFriends > 2) {
				savedFriend->setPosition(glm::vec2(44, 368));
				savedFriend->render();
				if(savedFriends > 3) {
					savedFriend->setPosition(glm::vec2(64, 368));
					savedFriend->render();
					if(savedFriends > 4) {
						savedFriend->setPosition(glm::vec2(84, 368));
						savedFriend->render();
						if(savedFriends > 5) {
							savedFriend->setPosition(glm::vec2(104, 368));
							savedFriend->render();
						}
					}
				}
			}
		}
	}

	if(player->hasTimePowerUp())
		clock->render();
	
	if(player->hasBoots())
		boots->render();
}

void GUI::setSprite(Sprite* sprite, glm::vec2 displacement) {
    sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 1);
	sprite->addKeyframe(0, displacement);
    sprite->changeAnimation(0);
}
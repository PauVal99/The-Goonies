#ifndef _SOUNDENGINE_INCLUDE
#define _SOUNDENGINE_INCLUDE
#include <irrKlang.h>

using namespace irrklang;

class SoundEngine
{
private:
	static SoundEngine* instance;
	SoundEngine();

public:
	static SoundEngine* getInstance();
	void playMainTheme();
	void playHit();
	void playJump();
	void playOpenDoor();
	void playPickUpKey();
	void playPortal();
	void playPickUpPowerUp();
	void playPutKey();
	void playEnemyDeath();

private:

	ISoundEngine* engine;
	ISoundSource* mainTheme;
	ISoundSource* hit;
	ISoundSource* jump;
	ISoundSource* openDoor;
	ISoundSource* pickUpKey;
	ISoundSource* portal;
	ISoundSource* putKey;
	ISoundSource* pickUpPowerUp;
	ISoundSource* enemyDeath;
};


#endif // _SCENE_INCLUDE

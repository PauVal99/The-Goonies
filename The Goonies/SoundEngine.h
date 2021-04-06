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
	void stopAllSounds();
	void playMainTheme();
	void playHit();
	void playJump();
	void playOpenDoor();
	void playPickUpKey();
	void playPortal();
	void playPickUpPowerUp();
	void playPutKey();
	void playEnemyDeath();
	void playGameOver();
	void playTheEnd();
	void playPunch();
	void playRescue();

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
	ISoundSource* gameOver;
	ISoundSource* theEnd;
	ISoundSource* punch;
	ISoundSource* rescue;

};


#endif // _SCENE_INCLUDE

#include "SoundEngine.h"



SoundEngine* SoundEngine::instance = 0;

SoundEngine* SoundEngine::getInstance(){
	
	if (instance == 0) {
		instance = new SoundEngine();
	}
	return instance;
}

SoundEngine::SoundEngine() {
	engine = createIrrKlangDevice();
	
	mainTheme = engine->addSoundSourceFromFile("sounds/MainTrack.mp3");
	hit = engine->addSoundSourceFromFile("sounds/Hit.wav");
	jump = engine->addSoundSourceFromFile("sounds/Jump.wav");
	putKey = engine->addSoundSourceFromFile("sounds/PutKey.wav");
	portal = engine->addSoundSourceFromFile("sounds/Portal.wav");
	openDoor = engine->addSoundSourceFromFile("sounds/OpenDoor.wav");
	pickUpKey = engine->addSoundSourceFromFile("sounds/PickUpKey.wav");
	pickUpPowerUp = engine->addSoundSourceFromFile("sounds/PickUpPowerUp.wav");
	enemyDeath = engine->addSoundSourceFromFile("sounds/EnemyDeath.wav");
	gameOver = engine->addSoundSourceFromFile("sounds/GameOver.mp3");
	theEnd = engine->addSoundSourceFromFile("sounds/TheEnd.mp3");
	punch = engine->addSoundSourceFromFile("sounds/Punch.wav");
	rescue = engine->addSoundSourceFromFile("sounds/Rescue.wav");

	mainTheme->setDefaultVolume(0.6f);
	jump->setDefaultVolume(0.35f);
	putKey->setDefaultVolume(0.35f);
	portal->setDefaultVolume(0.35f);
	openDoor->setDefaultVolume(0.35f);
	pickUpKey->setDefaultVolume(0.35f);
	pickUpPowerUp->setDefaultVolume(0.25f);
	enemyDeath->setDefaultVolume(0.6f);
	punch->setDefaultVolume(0.6f);
}

void SoundEngine::stopAllSounds() {
	engine->stopAllSounds();
}

void SoundEngine::playPunch() {
	engine->play2D(punch);
}

void SoundEngine::playRescue() {
	engine->play2D(rescue);
}

void SoundEngine::playGameOver() {
	engine->play2D(gameOver);
}

void SoundEngine::playTheEnd() {
	engine->play2D(theEnd);
}

void SoundEngine::playMainTheme() {
	engine->play2D(mainTheme, true);
}

void SoundEngine::playHit() {
	engine->play2D(hit);
}

void SoundEngine::playJump() {
	engine->play2D(jump);
}

void SoundEngine::playPutKey() {
	engine->play2D(putKey);
}

void SoundEngine::playPortal() {
	engine->play2D(portal);
}

void SoundEngine::playOpenDoor() {
	engine->play2D(openDoor);
}

void SoundEngine::playPickUpKey() {
	engine->play2D(pickUpKey);
}

void SoundEngine::playPickUpPowerUp() {
	engine->play2D(pickUpPowerUp);
}

void SoundEngine::playEnemyDeath() {
	engine->play2D(enemyDeath);
}

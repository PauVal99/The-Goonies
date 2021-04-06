#include "Enemy.h"
#include "SoundEngine.h"

void Enemy::die() {
    SoundEngine::getInstance()->playEnemyDeath();
    end();
}

bool Enemy::isDead() {
    return isEnded();
}
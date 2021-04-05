#include "Enemy.h"

void Enemy::die() {
    end();
}

bool Enemy::isDead() {
    return isEnded();
}
#include "PowerUp.h"

PowerUp::PowerUp() {

};

void PowerUp::render() {

	sprite->render();

}

void PowerUp::update(int deltaTime) {

	sprite->update(deltaTime);

}
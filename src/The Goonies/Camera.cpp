#include "Camera.h"

void Camera::update(glm::ivec2 position) {
    translation = glm::vec2(-(position.x / screenWidth) * screenWidth, -(position.y / screenHeight) * screenHeight);
}

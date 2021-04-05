#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(int screenWidth, int screenHeight) {
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
    }

	void update(glm::ivec2 position);
    inline glm::vec2 getTranslation() const { return translation; };

private:
	int screenWidth, screenHeight;
    glm::vec2 translation;
    
};


#ifndef _SPRITE_INCLUDE
#define _SPRITE_INCLUDE


#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"


// This class is derived from code seen earlier in TexturedQuad but it is also
// able to manage animations stored as a spritesheet. 


class Sprite
{

public:
	// Textured quads can only be created inside an OpenGL context
	static Sprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	Sprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);

	void update(int deltaTime);
	void render() const;
	void free();

	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	void pauseAnimation();
	void startAnimation();
	int animation() const;
	
	void setPosition(const glm::vec2 &pos);
	void setSize(const glm::vec2 &size);
	void setColor(const glm::vec4 &color);

private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao, vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position = glm::vec2(0.f), texCoordDispl, sizeInSpritesheet;
	int currentAnimation = -1, currentKeyframe;
	float timeAnimation;
	vector<AnimKeyframes> animations;
	bool pause = false;
	glm::vec4 color = glm::vec4(1.0f);
};


#endif // _SPRITE_INCLUDE


#pragma once
#include <Engine/Renderable.h>

class Cube : public IRenderable
{	
	GLuint program;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint texture = 0;
	GLuint textureID;
	GLuint mvpID;

	glm::mat4 modelMatrix;
public:
	Cube(const char* path, float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f);
	~Cube();

	void Update() {};
	void Render();
	void SetTexture(const char* path);
};


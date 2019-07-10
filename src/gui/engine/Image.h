#pragma once
#include <Engine/Renderable.h>

class Mesh;
class Image : public IRenderable
{
	typedef void (*FuncOnClick)();
	GLuint programID_image;
	//GLuint vertexbuffer_image;
	//GLuint uvbuffer_image;
	GLuint texture = 0;
	GLuint textureID;
	GLuint rectID;
	GLuint screenWidthID;
	GLuint screenHeightID;
	GLuint statusID;
	GLuint colorID;

	GLfloat x, y, w, h;
protected:
	glm::vec4 color;

public:
	GLfloat status;
	FuncOnClick onClick = nullptr;
	

public:
	Image(const char* path, float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f, glm::vec4 color = glm::vec4(1,1,1,1));
	~Image();

	void Update();
	void Render();
	void SetTexture(const char* path);
	

private:
	bool RayCast(float x, float y);
};


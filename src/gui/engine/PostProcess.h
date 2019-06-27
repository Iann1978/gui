#pragma once
class PostProcess
{
public:
	GLuint framebuffer = 0;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint texture = 0;


	GLuint program;
	GLuint textureID;
	GLuint screenWidthID;
	GLuint screenHeightID;


public:

	PostProcess();
	~PostProcess();

	void Render();
};


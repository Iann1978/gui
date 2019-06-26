#pragma once
class PostProcess
{
public:
	GLuint FramebufferName = 0;
	GLuint renderedTexture;
	GLuint programID_image;
	GLuint vertexbuffer_image;
	GLuint uvbuffer_image;
	GLuint texture = 0;
	GLuint textureID;
	GLuint rectID;
	GLuint screenWidthID;
	GLuint screenHeightID;
	GLuint statusID;

public:

	PostProcess();
	~PostProcess();

	void Render();
};


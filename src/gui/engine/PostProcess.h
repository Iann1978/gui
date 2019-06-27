#pragma once
class PostProcess
{
public:
	GLuint framebuffer[2];
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint texture[2];


	GLuint program[2];
	GLuint textureID[2];
	GLuint screenWidthID[2];
	GLuint screenHeightID[2];
	int currentBufferIndex = 0;


public:

	GLuint GetCurrentFrameBuffer() { return framebuffer[currentBufferIndex]; }
	PostProcess();
	~PostProcess();
	

	void Render();
	void RenderPass();
};


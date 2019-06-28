#pragma once
class PostProcess_Blur;
class PostProcess
{
public:
	GLuint framebuffer[2];
	GLuint texture[2];
	int currentBufferIndex = 0;
	PostProcess_Blur *blur = nullptr;

public:

	GLuint GetCurrentFrameBuffer() { return framebuffer[currentBufferIndex]; }
	PostProcess();
	~PostProcess();
	

	void Render();

};


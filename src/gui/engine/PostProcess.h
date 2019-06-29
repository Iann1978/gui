#pragma once
class PostProcess_Blur;
class PostProcess_Bloom;
class PostProcess
{
public:
	GLuint framebuffer[2];
	GLuint texture[2];
	int currentBufferIndex = 0;
	PostProcess_Blur *blur = nullptr;
	PostProcess_Bloom *bloom = nullptr;

public:

	GLuint GetCurrentFrameBuffer() { return framebuffer[currentBufferIndex]; }
	PostProcess();
	~PostProcess();
	

	void Render();

};


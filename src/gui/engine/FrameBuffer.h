#pragma once
class FrameBuffer
{
public:
	GLuint framebuffer;
	GLuint texture;
	GLuint depthstencilbuffer;
	GLuint stencilbuffer;
public:
	FrameBuffer();
	~FrameBuffer();
};


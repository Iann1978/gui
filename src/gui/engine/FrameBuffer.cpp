#include "prebuild.h"

#include <Engine/FrameBuffer.h>
#include <Engine/Screen.h>



FrameBuffer::FrameBuffer()
{

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Screen::width, Screen::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	glGenRenderbuffers(1, &depthstencilbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthstencilbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Screen::width, Screen::height);
	

	//glGenRenderbuffers(1, &stencilbuffer);
	//glBindRenderbuffer(GL_RENDERBUFFER, stencilbuffer);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, Screen::width, Screen::height);


	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthstencilbuffer);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencilbuffer);
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Error in %s.", __FUNCTION__);
	}

}


FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &framebuffer); framebuffer = 0;
	glDeleteTextures(1, &texture); texture = 0;
	glDeleteRenderbuffers(1, &depthstencilbuffer); depthstencilbuffer = 0;
	glDeleteRenderbuffers(1, &stencilbuffer); stencilbuffer = 0;
}




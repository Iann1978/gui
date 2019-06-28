#include "prebuild.h"
#include "PostProcess.h"
#include <engine/PostProcess_Blur.h>
#include <engine/Screen.h>
#include <engine/Shader.h>


PostProcess::PostProcess()
{
	blur = new PostProcess_Blur(this);

	// Generate render textures
	glGenTextures(2, texture);
	for (int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::width, Screen::height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	   
	glGenFramebuffers(2, framebuffer);
	for (int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer[i]);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture[i], 0);
		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers); 
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			printf("Error in PostProcess::PostProcess()");
		}
	}
}


PostProcess::~PostProcess()
{
}

void PostProcess::Render()
{
	blur->Render();
	return;
	
	
}
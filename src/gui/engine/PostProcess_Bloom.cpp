#include "prebuild.h"
#include "PostProcess_Bloom.h"
#include <engine/Screen.h>
#include <engine/Shader.h>
#include <engine/PostProcess.h>


PostProcess_Bloom::PostProcess_Bloom(PostProcess *process)
{
	this->process = process;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Screen::width, Screen::height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	static const GLfloat g_vertex_buffer_data_image[] = {
	-1.0f,-1.0f,0.0f,
	-1.0f,1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	-1.0f,-1.0f,0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f,-1.0f,0.0f,
	};

	static const GLfloat g_uv_buffer_data_image[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_image), g_vertex_buffer_data_image, GL_STATIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_image), g_uv_buffer_data_image, GL_STATIC_DRAW);




	Shader* shader[2];
	shader[0] = Shader::Find("PostProcess_HBlur");
	shader[1] = Shader::Find("PostProcess_VBlur"); 
	for (int i = 0; i < 2; i++)
	{
		program[i] = shader[i]->program;
		textureID[i] = glGetUniformLocation(program[i], "myTextureSampler");
		screenWidthID[i] = glGetUniformLocation(program[i], "screenWidth");
		screenHeightID[i] = glGetUniformLocation(program[i], "screenHeight");
	}


	Shader* shaderAdd = Shader::Find("PostProcess_Add");
	programOfAddPass = shaderAdd->program;
	texture0ID_inAddPass = glGetUniformLocation(programOfAddPass, "texture0");
	texture1ID_inAddPass = glGetUniformLocation(programOfAddPass, "texture1");
}


PostProcess_Bloom::~PostProcess_Bloom()
{
}

void PostProcess_Bloom::RenderAddPass()
{
	glUseProgram(programOfAddPass);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, process->texture[process->currentBufferIndex]);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(texture0ID_inAddPass, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texture1ID_inAddPass, 1);






	//glUniform4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void PostProcess_Bloom::RenderBlurPass()
{
	glUseProgram(program[process->currentBufferIndex]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, process->texture[process->currentBufferIndex]);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID[process->currentBufferIndex], 0);



	glUniform1f(screenWidthID[process->currentBufferIndex], Screen::width);
	glUniform1f(screenHeightID[process->currentBufferIndex], Screen::height);



	//glUniform4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void PostProcess_Bloom::Render()
{
	
	
	glReadBuffer(GL_COLOR_ATTACHMENT0);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, Screen::width, Screen::height, 0);


	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, process->framebuffer[(process->currentBufferIndex + 1) % 2]);
	RenderBlurPass();
	process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	RenderAddPass();
	//RenderBlurPass();
	//process->currentBufferIndex = (process->currentBufferIndex + 1) % 2;
}
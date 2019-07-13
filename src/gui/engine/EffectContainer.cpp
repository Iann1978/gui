#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include "EffectContainer.h"

#include <Engine/Shader.h>
#include <Engine/Region.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Color.h>
#include <Engine/FrameBuffer.h>

EffectContainer::EffectContainer(Mesh *mesh, glm::vec4 color)
{
	this->mesh = mesh;
	this->color = color;
	framebuffer0 = new FrameBuffer();
	framebuffer1 = new FrameBuffer();
	LoadBasePass();
	LoadTemplatePass();
	LoadAddPass();
}


EffectContainer::~EffectContainer()
{
}

void EffectContainer::Render()
{
	if (dirty)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		RenderBasePass(Color::black);

		for (int i = 0; i < 15; i++)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
			RenderTemplatePass(framebuffer0->texture);

			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
			RenderTemplatePass(framebuffer1->texture);
		}
		dirty = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearStencil(0);
	glStencilMask(~0);
	glClear(GL_STENCIL_BUFFER_BIT);
	RenderMaskPass();

	RenderAddPass(framebuffer1->texture);
}

void EffectContainer::LoadBasePass()
{

	Shader *shader = Shader::Find("Region");
	program = shader->program;

	mainColorId = glGetUniformLocation(program, "mainColor");
	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");

}
void EffectContainer::RenderBasePass(glm::vec4 color)
{
	glUseProgram(program);

	glUniform4fv(mainColorId, 1, &color.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	Mesh::RenderMesh(mesh);
}
void EffectContainer::RenderMaskPass()
{
	glUseProgram(program);

	glUniform4fv(mainColorId, 1, &Color::black0.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_NEVER);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	Mesh::RenderMesh(mesh);
}
void EffectContainer::LoadTemplatePass()
{
	Shader *shader = Shader::Find("Template");
	programOfTemplatePass = shader->program;


	baseWidthID = glGetUniformLocation(programOfTemplatePass, "baseWidth");
	baseHeightID = glGetUniformLocation(programOfTemplatePass, "baseHeight");
	templateWidthID = glGetUniformLocation(programOfTemplatePass, "templateWidth");
	templateHeightID = glGetUniformLocation(programOfTemplatePass, "templateHeight");
	baseTextureID = glGetUniformLocation(programOfTemplatePass, "baseTexture");
	templateTextureID = glGetUniformLocation(programOfTemplatePass, "templateTexture");
	templateColorScaleID = glGetUniformLocation(programOfTemplatePass, "templateColorScale");

	//templateTexture = loadBMP_custom("images/template-white-5x5.bmp");
	templateTexture = generateGaussianTemplate();
}

void EffectContainer::RenderTemplatePass(GLuint texture)
{
	glUseProgram(programOfTemplatePass);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(baseTextureID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, templateTexture);
	glUniform1i(templateTextureID, 1);

	glm::vec4 templateColorScale = Color::white * 1.02f;
	glUniform4fv(templateColorScaleID, 1, &templateColorScale.x);
	glUniform1i(baseWidthID, Screen::width);
	glUniform1i(baseHeightID, Screen::height);
	glUniform1i(templateWidthID, 5);
	glUniform1i(templateHeightID, 5);



	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);

	Mesh::RenderMesh(Mesh::quad3);
}


void EffectContainer::LoadAddPass()
{
	Shader* shaderAdd = Shader::Find("ColorTexture");
	programOfAddPass = shaderAdd->program;
	baseTextureID_inAddPass = glGetUniformLocation(programOfAddPass, "baseTexture");
	colorID_inAddPass = glGetUniformLocation(programOfAddPass, "color");
}
void EffectContainer::RenderAddPass(GLuint texture)
{
	glUseProgram(programOfAddPass);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(baseTextureID_inAddPass, 0);
	glm::vec4 tmpcolor = color * 2.0f;
	glUniform4fv(colorID_inAddPass, 1, &tmpcolor.x);


	glEnable(GL_BLEND);

	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0x00);
	glStencilFunc(GL_EQUAL, 0xFF, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	Mesh::RenderMesh(Mesh::quad3);

	//glDisable(GL_STENCIL_TEST);

}
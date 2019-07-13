#include "prebuild.h"
#include "GradientRampEffect.h"

#include <Engine/Mesh.h>
#include <Engine/Shader.h>
#include <Engine/Color.h>
#include <Engine/Screen.h>



GradientRampEffect::GradientRampEffect(Mesh *mesh)
{
	
	LoadGradientPass();
	LoadStencilPass(mesh);
}


GradientRampEffect::~GradientRampEffect()
{
}

void GradientRampEffect::Render()
{
	RenderStencilPass(); 
	RenderGradientPass();
}


void GradientRampEffect::LoadGradientPass()
{
	//gradientMesh = Mesh::CreateMesh(glm::vec4(400, 468, 300, 200));
	gradientMesh = Mesh::CreateGradientMesh(glm::vec4(400, 468, 300, 200), Color::black, glm::vec4(0.30, 0.75, 0.98, 1));
	
	gradientShader = Shader::Find("VertexColor");
	mainColorId = gradientShader->GetLocation("mainColor");
	screenWidthID = gradientShader->GetLocation("screenWidth");
	screenHeightID = gradientShader->GetLocation("screenHeight");
}

void GradientRampEffect::RenderGradientPass()
{
	glUseProgram(gradientShader->program);

	glUniform4fv(mainColorId, 1, &Color::white.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	// Depth status
	glDisable(GL_DEPTH_TEST);

	// Stencil status
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0);
	glStencilFunc(GL_EQUAL, 0xFF, ~0);
	//glDisable(GL_STENCIL_TEST); // temp 

	// Blend status
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);


	Mesh::RenderMesh(gradientMesh);
}

void GradientRampEffect::LoadStencilPass(Mesh *stencilMesh)
{
	this->stencilMesh = stencilMesh;
	stencilShader = Shader::Find("Region");
	mainColorId = stencilShader->GetLocation("mainColor");
	screenWidthID = stencilShader->GetLocation("screenWidth");
	screenHeightID = stencilShader->GetLocation("screenHeight");
}

void GradientRampEffect::RenderStencilPass()
{
	glClearStencil(0);
	glStencilMask(~0);
	glClear(GL_STENCIL_BUFFER_BIT);

	glUseProgram(stencilShader->program);

	glUniform4fv(mainColorId, 1, &Color::white.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	// Depth status
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_NEVER);

	// Stencil status
	glEnable(GL_STENCIL_TEST);
	glStencilMask(~0);
	glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	// Blend status
	glDisable(GL_BLEND);

	Mesh::RenderMesh(stencilMesh);
}
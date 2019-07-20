#include "prebuild.h"
#include "MaskedShapes.h"
#include <Engine/Curve.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>
#include <Engine/Shader.h>
#include <Engine/Screen.h>
#include <Engine/Color.h>

MaskedShapes::MaskedShapes()
{
	LoadStencilPass();
	LoadGradientPass();
	
}


MaskedShapes::~MaskedShapes()
{
}

void MaskedShapes::Render()
{
	ClearStencil();
	RenderStencilPass();
	RenderGradientPass();
}

void MaskedShapes::ClearStencil()
{
	glStencilMask(~0);
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
}


void MaskedShapes::LoadStencilPass()
{
	std::vector<glm::vec3> points;
	points.clear();
	points.push_back(glm::vec3(512, 756, 0));
	points.push_back(glm::vec3(589, 756, 0));
	points.push_back(glm::vec3(850, 380, 0));
	points.push_back(glm::vec3(822, 340, 0));
	points.push_back(glm::vec3(275, 340, 0));
	points.push_back(glm::vec3(250, 380, 0));
	stencilMesh = Mesh::CreatePolygon(points);

	Shader *shader = Shader::Find("Region");
	stencilMat = new Material(shader);
	stencilMat->SetFloat("screenWidth", Screen::width);
	stencilMat->SetFloat("screenHeight", Screen::height);
	stencilMat->SetVector("mainColor", Color::black0);
}

void MaskedShapes::RenderStencilPass()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_NEVER);

	// Stencil status
	glEnable(GL_STENCIL_TEST);
	glStencilMask(~0);
	glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);


	glDisable(GL_BLEND);
	
	stencilMat->Use();
	Mesh::RenderMesh(stencilMesh);

}

void  MaskedShapes::LoadGradientPass()
{
	std::vector<glm::vec3> points;
	points.push_back(glm::vec3(690, 586, 0));
	points.push_back(glm::vec3(1090, 586, 0));

	std::vector<glm::vec4> colors;
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0));
	gradient = new Curve(points, colors, 25);

	points.clear();
	points.push_back(glm::vec3(800, 423, 0));
	points.push_back(glm::vec3(1050, 423, 0));
	gradient1 = new Curve(points, colors, 25);

	points.clear();
	points.push_back(glm::vec3(290, 423, 0));
	points.push_back(glm::vec3(40, 423, 0));
	gradient2 = new Curve(points, colors, 25);

}
void  MaskedShapes::RenderGradientPass()
{
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0);
	glStencilFunc(GL_NOTEQUAL, 0xFF, ~0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gradient->material->Use();
	Mesh::RenderMesh(gradient->mesh);
	Mesh::RenderMesh(gradient1->mesh);
	Mesh::RenderMesh(gradient2->mesh);

	//gradient->Render();
}
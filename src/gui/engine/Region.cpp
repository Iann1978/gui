#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Region.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Color.h>
#include <Engine/FrameBuffer.h>
#include <Engine/EffectContainer.h>
#include <Engine/GradientRampEffect.h>
#include <Engine/Material.h>


#include <vector>

Region::Region(glm::vec4 rect, glm::vec4 color, Effect effect)
{
	this->type = Rect;
	this->effect = effect;
	this->rect = rect;
	this->color = color;
	LoadRect(rect, color);
}

Region::Region(std::vector<glm::vec3> polygon, glm::vec4 color, Effect effect)
{
	this->type = Polygon;
	this->effect = effect;
	this->color = color;
	LoadPolygon(polygon);
}

Region::~Region()
{
	if (material)
	{
		delete material;
		material = nullptr;
	}
}

void Region::Render()
{
	switch (effect)
	{
	case Effect::Fill: RenderFill(); break;
	case Effect::FadeInEdge: RenderFadeInEdge(); break;
	case Effect::GradientRamp: RenderGradientRamp(); break;
	default: printf("Error in Region::Render");
	}
}

void Region::Update()
{
}

void Region::LoadRect(glm::vec4 rect, glm::vec4 color)
{
	this->rect = rect;
	this->color = color;

	Shader *shader = Shader::Find("Region");
	material = new Material(shader);
	material->SetVector("mainColor", color);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);

	mesh = Mesh::CreateQuad(rect);

	effectContainer = new EffectContainer(mesh, color);
}



void Region::LoadPolygon(std::vector<glm::vec3> polygon)
{
	mesh = Mesh::CreatePolygon(polygon);

	Shader *shader = Shader::Find("Region");
	material = new Material(shader);
	material->SetVector("mainColor", color);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);

	effectContainer = new EffectContainer(mesh, color);
	gradientRampEffect = new GradientRampEffect(mesh);
}


void Region::RenderFill()
{
	material->Use();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_STENCIL_TEST);

	Mesh::RenderMesh(mesh);
}
void Region::RenderFadeInEdge()
{
	effectContainer->Render();
}

void Region::RenderGradientRamp()
{
	gradientRampEffect->Render();
}

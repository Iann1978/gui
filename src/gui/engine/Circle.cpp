#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Circle.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>

Circle::Circle(glm::vec3 position, glm::vec3 color, float radius, float startAngle, float endAngle)
{
	this->color = color;
	this->radius = radius;
	this->startAngle = startAngle;
	this->endAngle = endAngle;

	radius = 25;
	LoadCross(position, color);
}


Circle::~Circle()
{
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}
}

void Circle::Render()
{
	RenderCross();
}

void Circle::Update()
{

}

void Circle::LoadCross(glm::vec3 position, glm::vec3 color)
{
	this->color = color;
	Shader *shader = Shader::Find("Circle");
	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);
	material->SetVector("centerColor", color);
	material->SetFloat("radius", radius);
	material->SetFloat("startAngle", startAngle);
	material->SetFloat("endAngle", endAngle);
	material->SetFloat("width", width);


	mesh = Mesh::CreatePoint(position, glm::vec4(color,1));
}
void Circle::RenderCross()
{
	material->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);
}




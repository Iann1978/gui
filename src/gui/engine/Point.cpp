#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Point.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>


Point::Point(glm::vec3 position, glm::vec3 color, Type type)
{
	this->type = type;

	if (type == Normal)
		LoadNormal(position, color);
	else if (type == Star)
		LoadStar(position, color);
	else if (type == Cross)
		LoadCross(position, color);
	else if (type == Polygon)
		LoadPolygon(position, color);
}


Point::~Point()
{
	if (mesh)
	{
		delete mesh;
		mesh = nullptr;
	}

	if (material)
	{
		delete material;
		material = nullptr;
	}
}

void Point::Render()
{
	if (type == Normal)
		RenderNormal();
	else if (type == Star)
		RenderStar();
	else if (type == Cross)
		RenderCross();
	else if (type == Polygon)
		RenderPolygon();
}

void Point::Update()
{
}

void Point::LoadNormal(glm::vec3 position, glm::vec3 color)
{
	Shader *shader = Shader::Find("Curve");
	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);

	mesh = Mesh::CreatePoint(position, glm::vec4(color.r, color.g, color.b, 1));
}

void Point::RenderNormal()
{
	material->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);
}

void Point::LoadStar(glm::vec3 position, glm::vec3 color)
{
	Shader *shader = Shader::Find("Point_Star");

	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);

	mesh = Mesh::CreatePoint(position, glm::vec4(color.r, color.g, color.b, 1));
}

void Point::RenderStar()
{
	material->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);
}

void Point::LoadCross(glm::vec3 position, glm::vec3 color)
{
	this->color = color;
	Shader *shader = Shader::Find("Point_Cross");
	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);
	material->SetVector("centerColor", color);

	mesh = Mesh::CreatePoint(position, glm::vec4(color.r, color.g, color.b, 1));
}

void Point::RenderCross()
{
	material->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);
}

void Point::LoadPolygon(glm::vec3 position, glm::vec3 color)
{
	this->color = color;

	Shader *shader = Shader::Find("Point_Polygon");
	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);
	material->SetVector("centerColor", color);
	material->SetFloat("angle", angle);

	mesh = Mesh::CreatePoint(position, glm::vec4(color.r, color.g, color.b, 1));
}
void Point::RenderPolygon()
{
	material->SetFloat("size", size);
	material->SetFloat("angle", angle);
	material->SetInt("segment", segment);
	material->Use();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);
}




#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Curve.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>

	
void Curve::LoadMesh(int pointNumber, float *vertexBufferData, float *colorBufferData)
{
	this->pointNumber = pointNumber;
	
	mesh = new Mesh(Mesh::Type::LineStrip, pointNumber*3, vertexBufferData,
		0, nullptr,
		pointNumber*4, colorBufferData,
		pointNumber, nullptr);
}

void Curve::LoadMaterial()
{	
	Shader *shader = Shader::Find("Curve");
	material = new Material(shader);
	material->SetFloat("screenWidth", Screen::width);
	material->SetFloat("screenHeight", Screen::height);
	material->SetFloat("width", width);
}

Curve::Curve(int pointNumber, float *vertexBufferData, float *colorBufferData)
{	
	LoadMaterial();
	LoadMesh(pointNumber, vertexBufferData, colorBufferData);
}

Curve::Curve(std::vector<glm::vec3> points, glm::vec4 color, float width)
{
	this->width = width;
	std::vector<glm::vec4> colors(points.size(), color);
	LoadMaterial();
	LoadMesh(points.size(), &points[0].x, &colors[0].x);
}

Curve::Curve(std::vector<glm::vec3> points, std::vector<glm::vec4> colors, float width)
{
	this->width = width;
	LoadMaterial();
	LoadMesh(points.size(), &points[0].x, &colors[0].x);
}

Curve::~Curve()
{
	delete mesh;
}

void Curve::Render()
{
	material->Use();



	glDisable(GL_DEPTH_TEST);

	glDisable(GL_STENCIL_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glLineWidth(5);
	glEnable(GL_LINE_SMOOTH);

	GLfloat lineWidthRange[2] = { 0.0f, 0.0f };
	glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);



	Mesh::RenderMesh(mesh);

}

void Curve::Update()
{
	
}
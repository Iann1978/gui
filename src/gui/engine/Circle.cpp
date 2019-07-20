#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Circle.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>






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
	
	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &colorbuffer);
	//glDeleteProgram(program);
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
	program = shader->program;

	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");
	centerColorID = glGetUniformLocation(program, "centerColor");
	radiusID = glGetUniformLocation(program, "radius");
	startAngleID = glGetUniformLocation(program, "startAngle");
	endAngleID = glGetUniformLocation(program, "endAngle");


	mesh = Mesh::CreatePoint(position, glm::vec4(color,1));
	//glGenBuffers(1, &vertexbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, &position, GL_STATIC_DRAW);


	//glGenBuffers(1, &colorbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, &color, GL_STATIC_DRAW);
}
void Circle::RenderCross()
{

	glUseProgram(program);

	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);
	glUniform1f(radiusID, radius);
	glUniform1f(startAngleID, startAngle);
	glUniform1f(endAngleID, endAngle);

	glUniform3f(centerColorID, color.r, color.g, color.b);

	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(
	//	0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
	//	3,                  // size
	//	GL_FLOAT,           // type
	//	GL_FALSE,           // normalized?
	//	0,                  // stride
	//	(void*)0            // array buffer offset
	//);

	//// 2nd attribute buffer : UVs
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glVertexAttribPointer(
	//	1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	//	3,                                // size : U+V => 2
	//	GL_FLOAT,                         // type
	//	GL_FALSE,                         // normalized?
	//	0,                                // stride
	//	(void*)0                          // array buffer offset
	//);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glPointSize(15.0f);

	Mesh::RenderMesh(mesh);

	//// Draw the triangle !
	//glDrawArrays(GL_POINTS, 0, 1); // 12*3 indices starting at 0 -> 12 triangles

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

}




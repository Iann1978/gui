#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Region.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>






Region::Region(glm::vec4 rect, glm::vec4 color)
{
	this->type = type;
	this->rect = rect;
	this->color = color;
	Shader *shader = Shader::Find("Region");
	program = shader->program;
	
	mainColorId = glGetUniformLocation(program, "mainColor");


	float x = rect.x;
	float y = rect.y;
	float w = rect.z;
	float h = rect.w;

	float vertexBufferData[] = {
		x,		y,		0.0f,
		x + w,	y,		0.0f,
		x + w,	y + h,	0.0f,
		x,		y,		0.0f,
		x + w,	y + h,	0.0f,
		x,		y + h,	0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertexBufferData, GL_STATIC_DRAW);
}


Region::~Region()
{
	glDeleteBuffers(1, &vertexbuffer);
}

void Region::Render()
{
	glUseProgram(program);


	glUniform4fv(mainColorId, 1, &color.x);

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



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);


	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); 

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


}

void Region::Update()
{

}

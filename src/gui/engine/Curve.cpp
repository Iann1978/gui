#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Curve.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>



	


Curve::Curve(int pointNumber, float *vertexBufferData, float *colorBufferData)
{

	this->pointNumber = pointNumber;
	//shader = LoadShaders("shaders/Curve_vert.shader", "shaders/Curve_frag.shader");
	Shader *shader = Shader::Find("Curve");
	program = shader->program;

	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, pointNumber * sizeof(float) * 3, vertexBufferData, GL_STATIC_DRAW);


	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, pointNumber * sizeof(float) * 3, colorBufferData, GL_STATIC_DRAW);
}


Curve::~Curve()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	//glDeleteProgram(program);
}

void Curve::Render()
{

	glUseProgram(program);

	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);
	
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
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the triangle !
	glDrawArrays(GL_LINE_STRIP, 0, pointNumber); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Curve::Update()
{
	
}
#include "prebuild.h"
#include <common/shader.hpp>
#include <common/texture.hpp>


#include <Engine/Curve.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>





Curve::Curve()
{
	static const GLfloat vertexBufferData[] = {
		0.0f,45.0f,0.0f,
		1920.0f, 45.0f, 0.0f,
	};

	static const GLfloat colorBufferData[] = {
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
	};

	shader = LoadShaders("shaders/Curve_vert.shader", "shaders/Curve_frag.shader");
	screenWidthID = glGetUniformLocation(shader, "screenWidth");
	screenHeightID = glGetUniformLocation(shader, "screenHeight");
	
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);


	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
}


Curve::~Curve()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(shader);
}

void Curve::Render()
{

	glUseProgram(shader);

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
	glDrawArrays(GL_LINES, 0, 2); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Curve::Update()
{
	
}
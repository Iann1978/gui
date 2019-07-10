#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Image.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>





Image::Image(const char* path, float x, float y, float w, float h, glm::vec4 color)
{
	this->color = color;
	this->status = 0.7 * (rand() %5)/5;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	static const GLfloat g_vertex_buffer_data_image[] = {
		0.0f,0.0f,0.0f,
		0.0f,1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f,0.0f,0.0f,
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	static const GLfloat g_uv_buffer_data_image[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	x = y = 0.0f;
	w = h = 0.5f;
	//texture = loadDDS("uvtemplate.DDS");
	texture = loadDDS(path);
	//texture = loadDDS("1.dds");
	Shader *shader = Shader::Find("Image");
	//programID_image = LoadShaders("shaders/Image_vert.shader", "shaders/Image_frag.shader");
	programID_image = shader->program;
	textureID = glGetUniformLocation(programID_image, "myTextureSampler");
	rectID = glGetUniformLocation(programID_image, "rect");
	screenWidthID = glGetUniformLocation(programID_image, "screenWidth");
	screenHeightID = glGetUniformLocation(programID_image, "screenHeight");
	statusID = glGetUniformLocation(programID_image, "status");
	colorID = glGetUniformLocation(programID_image, "color");
	
	//glGenBuffers(1, &vertexbuffer_image);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_image);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_image), g_vertex_buffer_data_image, GL_STATIC_DRAW);

	//
	//glGenBuffers(1, &uvbuffer_image);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_image), g_uv_buffer_data_image, GL_STATIC_DRAW);
}


Image::~Image()
{
	//glDeleteBuffers(1, &uvbuffer_image);
	//glDeleteBuffers(1, &vertexbuffer_image);
	glDeleteProgram(programID_image);
	glDeleteTextures(1, &texture);
}

void Image::SetTexture(const char* path)
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}
	
	texture = loadDDS(path);
}

bool Image::RayCast(float x, float y)
{
	return  (x >= this->x && x <= (this->x + this->w) &&
		y >= this->y && y <= (this->y + this->h));
}



void Image::Render()
{
	if (RayCast(Input::mousePosX, Input::mousePosY))
	{
		status = 0.3f;
	}
	else
	{
		status = 0.0f;
	}

	glUseProgram(programID_image);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	glUniform4fv(rectID, 1, &x);
	glUniform4fv(colorID, 1, &color.x);

	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);
	glUniform1f(statusID, status);
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	Mesh::RenderMesh(Mesh::quad2);

}

void Image::Update()
{
	if (Input::GetMouseButtonUp(Input::LeftButton) && RayCast(Input::mousePosX, Input::mousePosY))
	{
		//printf("click a image.\n");
		if (onClick)
		{
			onClick();
		}
	}
}
﻿// Include standard headers
#include "prebuild.h"
//GLFWwindow* window;

#include <list>


#include <common/common_shader.hpp>
#include <common/texture.hpp>
#include <common/text2D.hpp>

#include <Engine/Renderable.h>
#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Shader.h>
#include <Engine/Image.h>
#include <Engine/Text.h>
#include <Engine/Cube.h>
#include <Engine/Curve.h>
#include <Engine/Engine.h>


#include <StatusBar.h>


#pragma warning (disable: 4996)

Image* clickImage = nullptr;

void OnClick()
{
	printf("An image is clicked.\n");
	clickImage->SetTexture("images/volume.dds");
}

void CreateUI(std::list<IRenderable*>& renders)
{
	
	StatusBar* statusBar = new StatusBar();
	renders.push_back(statusBar);

	static GLfloat vertexBufferData[] = {
	0.0f,45.0f,0.0f,
	1920.0f, 45.0f, 0.0f,
	920.0f, 445.0f, 0.0f,
	};

	static GLfloat colorBufferData[] = {
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
	};
	Curve* curve = new Curve(3, vertexBufferData, colorBufferData);
	renders.push_back(curve);
	
	//return;
	int xint = 20;
	int yint = 20;
	int x = xint;
	int y = yint + 50;
	int width = 300;
	int height = 300;
	Image* image = new Image("images/1.dds", x, y, width, height);
	renders.push_back(image);
	Text* text = new Text("BEIJING WEST", x + 5, y + 230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y + 260, 20);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/3.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);


	x += xint + width;
	image = new Image("images/1.dds", x, y, width, height);
	clickImage = image;
	image->onClick = OnClick;
	renders.push_back(image);
	text = new Text("BEIJING WEST", x + 5, y + 230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y + 260, 20);
	renders.push_back(text);

	y += yint + height;
	x = xint;
	image = new Image("images/tech-feel-001.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/1.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("BEIJING WEST", x + 5, y + 230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y + 260, 20);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/3.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);
}

void CreateTechFeel001(std::list<IRenderable*>& renders)
{

	StatusBar* statusBar = new StatusBar();
	renders.push_back(statusBar);

	Image *image = new Image("images/tech-feel-001.dds", 0, 45, 1024, 1024);
	renders.push_back(image);

	static GLfloat vertexBufferData[] = {
		0.0f,45.0f,0.0f,
		1920.0f, 45.0f, 0.0f,
		920.0f, 445.0f, 0.0f,
	};

	static GLfloat colorBufferData[] = {
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
	};
	Curve* curve = new Curve(3, vertexBufferData, colorBufferData);
	renders.push_back(curve);

}

void DestroyUI(std::list<IRenderable*>& renders)
{
	for (std::list<IRenderable*>::iterator it = renders.begin();
		it != renders.end();
		it++)
	{
		delete (*it);
	}
}

void CreateGeo(std::list<IRenderable*>& renders)
{
	return;
	Cube* cube = new Cube("images/1.dds", 0, 0, 100, 100);
	renders.push_back(cube);
}

void DestroyGeo(std::list<IRenderable*>& renders)
{
	for (std::list<IRenderable*>::iterator it = renders.begin();
		it != renders.end();
		it++)
	{
		delete (*it);
	}
}

int main(void)
{
	Engine engine;
	Shader *shader = new Shader("Curve", "shaders/Curve_vert.shader", "shaders/Curve_frag.shader");
	shader = new Shader("Image", "shaders/Image_vert.shader", "shaders/Image_frag.shader");
	shader = new Shader("Text", "shaders/Text_vert.shader", "shaders/Text_frag.shader");
	//CreateGeo(engine.geolist);
	//CreateUI(engine.uilist);
	CreateTechFeel001(engine.uilist);

	engine.Run();

	DestroyGeo(engine.geolist);
	DestroyUI(engine.uilist);
	shader = Shader::Find("Curve");
	delete shader;
	shader = Shader::Find("Image");
	delete shader;
	shader = Shader::Find("Text");
	delete shader;

	return 0;
}


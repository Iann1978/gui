// Include standard headers
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
#include <Engine/Point.h>
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

void CreateCurve(std::list<IRenderable*>& renders, glm::vec3 color, int pointNumber, float *vertex)
{
	float *colorBufferData = new float[pointNumber * 3];
	float *vertexBufferData = new float[pointNumber * 3];
	for (int i = 0; i < pointNumber; i++)
	{
		vertexBufferData[i * 3 + 0] = vertex[i * 2 + 0];
		vertexBufferData[i * 3 + 1] = vertex[i * 2 + 1];
		vertexBufferData[i * 3 + 2] = 0;
		colorBufferData[i * 3 + 0] = color[0];
		colorBufferData[i * 3 + 1] = color[1];
		colorBufferData[i * 3 + 2] = color[2];
	}
	Curve* curve = new Curve(pointNumber, vertexBufferData, colorBufferData);
	renders.push_back(curve);

	Point *point = new Point(glm::vec3(vertex[0], vertex[1], 0), color);
	renders.push_back(point);

	delete colorBufferData;
	delete vertexBufferData;
	delete vertex;



}

void CreateTechFeel001(std::list<IRenderable*>& renders)
{

	StatusBar* statusBar = new StatusBar();
	renders.push_back(statusBar);

	Image *image = new Image("images/tech-feel-001.dds", 1024, 45, 1024, 1024);
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



	CreateCurve(renders, glm::vec3(1, 1, 1), 3,  new float[6] {0,955,55,1008,55,1075});
	CreateCurve(renders, glm::vec3(1, 1, 1), 2, new float[4]{ 41,837,41,941});
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 84,718,84,960,105,977,104,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 2, new float[4]{ 105,591,105,945 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 166,755,169,810,145,837,143,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 200,645,200,850,173,882,173,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 3, new float[6]{ 215,1001,257,1033,257,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 228,733,228,941,296,1020,296,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 265,820,265,920,330,980,330,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 294,605,294,887,358,978,358,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 329,704,329,911,384,970,384,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 457,635,457,766,417,814,417,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 512,564,512,775,456,832,456,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 621,626,623,731,483,870,483,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 2, new float[4]{ 533,948,533,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 516,865,516,884,597,965,597,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 571,821,571,864,647,931,647,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 607,784,607,824,678,888,678,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 3, new float[6]{ 631,811,699,879,699,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 660,493,660,771,729,847,729,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 6, new float[12]{ 679,573,679,762,751,838,751,894,772,922,772,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 2, new float[4]{ 807,570,804,830 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 837,631,837,836,798,881,798,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 876,736,876,850,824,905,824,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 901,622,901,943,869,981,869,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 2, new float[4]{ 927,1003,927,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 932,697,932,858,957,889,957,1075 });
	CreateCurve(renders, glm::vec3(1, 1, 1), 4, new float[8]{ 978,788,978,851,1005,877,1005,1075 });



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
	shader = new Shader("PostProcess_HBlur", "shaders/PostProcess_HBlur_vert.shader", "shaders/PostProcess_HBlur_frag.shader");
	shader = new Shader("PostProcess_VBlur", "shaders/PostProcess_VBlur_vert.shader", "shaders/PostProcess_VBlur_frag.shader");
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


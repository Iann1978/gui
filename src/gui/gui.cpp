// Include standard headers
#include "prebuild.h"
//GLFWwindow* window;

#include <list>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/text2D.hpp>

#include <Engine/Renderable.h>
#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Image.h>
#include <Engine/Text.h>
#include <Engine/Cube.h>
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
	image = new Image("images/3.dds", x, y, width, height);
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
	CreateGeo(engine.geolist);
	CreateUI(engine.uilist);

	engine.Run();

	DestroyGeo(engine.geolist);
	DestroyUI(engine.uilist);

	return 0;
}


// Include standard headers
#include "prebuild.h"

#include <set>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>

#include <Engine/Renderable.h>
#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Shader.h>
#include <Engine/Mesh.h>
#include <Engine/Image.h>
#include <Engine/Text.h>
#include <Engine/Cube.h>
#include <Engine/Curve.h>
#include <Engine/Point.h>
#include <Engine/Circle.h>
#include <Engine/Region.h>
#include <Engine/Engine.h>
#include <Engine/Serializer/CurveSerializer.h>


#include <editor/Command.h>



#include <demos/demo002/ProcessBar.h>
#include <StatusBar.h>
#include "MaskedShapes.h"
#include "MaskedShapes2.h"
#include "ColumnDiagram.h"




#pragma warning (disable: 4996)

using namespace demo002;

void CreateBackPoints(std::list<IRenderable*>& renders)
{
	float inteval = 1.0f* 1100 / 24;
	for (float x = inteval; x < 1090; x += inteval)
	{
		for (float y = inteval; y < 1090; y += inteval)
		{
			Point *point = new Point(glm::vec3(x, y, 0), glm::vec3(29.0f/255, 139.0f/255, 175.0f/255), Point::Type::Cross);
			renders.push_back(point);
		}
	}
}

Region * CreateRegion(int i, int j, int colorIndex)
{
	j = 23 - j;
	glm::vec4 colors[] = { glm::vec4(0.08873602, 0.4435053, 0.752, 0.3), glm::vec4(0.694, 0.5205, 0.5205, 0.2) };
	float inteval = 1.0f * 1100 / 24;
	Region *region = new Region(glm::vec4(i*inteval, j*inteval, inteval, inteval), colors[colorIndex]);
	return region;
}

void CreateBackgroundRects(std::list<IRenderable *>& renders)
{
	for (int j = 12; j < 23; j++)
	{
		int count = rand() % 8;
		count = (count != 0) ? count : (rand() % 8);
		count = (count != 0) ? count : (rand() % 8);
		count = (count != 0) ? count : (rand() % 8);
		std::set<int> rowSet;

		for (int i = 0; i < count; i++)
		{
			rowSet.insert(rand() % 24);
			
		}

		for (int row : rowSet)
		{
			renders.push_back(CreateRegion(row, j, rand() % 2));
		}

	}

	renders.push_back(CreateRegion(6, 1, 0));
	renders.push_back(CreateRegion(10, 1, 0));
	renders.push_back(CreateRegion(18, 1, 0));

	renders.push_back(CreateRegion(12, 2, 0));

	renders.push_back(CreateRegion(3, 3, 0));
	renders.push_back(CreateRegion(22, 3, 0));

	renders.push_back(CreateRegion(6, 4, 0));
	renders.push_back(CreateRegion(11, 4, 1));
	renders.push_back(CreateRegion(18, 4, 1));

	renders.push_back(CreateRegion(12, 5, 1));

	renders.push_back(CreateRegion(6, 6, 1));
	renders.push_back(CreateRegion(9, 6, 1));
	renders.push_back(CreateRegion(21, 6, 0));

	renders.push_back(CreateRegion(11, 7, 1));
	renders.push_back(CreateRegion(20, 7, 1));

	renders.push_back(CreateRegion(7, 8, 1));
	renders.push_back(CreateRegion(9, 8, 1));
	renders.push_back(CreateRegion(11, 8, 1));
	renders.push_back(CreateRegion(12, 8, 1));
	renders.push_back(CreateRegion(13, 8, 1));
	renders.push_back(CreateRegion(16, 8, 1));

	renders.push_back(CreateRegion(1, 9, 0));
	renders.push_back(CreateRegion(9, 9, 1));
	renders.push_back(CreateRegion(19, 9, 1));

	renders.push_back(CreateRegion(8, 10, 1));

	renders.push_back(CreateRegion(8, 11, 1));
	renders.push_back(CreateRegion(20, 11, 0));
	renders.push_back(CreateRegion(22, 11, 1));

}

class Background : public Image
{
public:
	Background();
	void Update() override;
};

Background::Background()
	: Image("images/fake002.dds", 0, 0, Screen::width/2, Screen::height, glm::vec4(1, 1, 1, 0.4)) {}
void Background::Update()
{
	if (Input::GetKeyDown(Input::KeyCode::KeyQ))
	{
		color.a = (color.a == 0) ? 0.4 : 0;
	}
}

class ShowMousePosition : public IRenderable
{
	// mousepos
	char mouseposstr[100];
	Text* mousepos;
	void UpdateMousePos()
	{
		int x = Input::mousePosX;
		int y = Input::mousePosY;
		sprintf_s(mouseposstr, sizeof(mouseposstr), "%d:%d", x, y);
	}

public:
	ShowMousePosition()
	{
		mousepos = new Text(mouseposstr, 5, 5, 24);
		UpdateMousePos();
	}

	void Update()
	{
		UpdateMousePos();
	}
	void Render()
	{
		mousepos->Render();
	}
};
class ShowFps : public IRenderable
{
	float fps = 0;
	char fpsstr[100];
	Text* text;
	float lastTime;
	
public:

	ShowFps()
	{
		sprintf_s(fpsstr, sizeof(fpsstr), "fps:%5.2f", fps);
		text = new Text(fpsstr, 225, 5, 24);
	}

	void Update()
	{
		if (Time::frameCounter % 15 == 0)
		{
			float curTime = Time::time;
			fps = 15 / (curTime - lastTime);
			sprintf_s(fpsstr, sizeof(fpsstr), "fps:%5.2f",fps);
			lastTime = curTime;
		}
	}
	void Render()
	{
		text->Render();
	}
};

Region *CreatePolygon(std::vector<glm::vec3> polygon)
{
	//for (glm::vec3& p : polygon)
	//{
	//	p.x = p.x / Screen::width * 2 - 1;
	//	p.y = 1 - p.y / Screen::height * 2;
	//	p.z = 0;
	//}
	Region *region = new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 1));
	return region;
}

void CreatePolygons(std::list<IRenderable *>& renders)
{
	std::vector<glm::vec3> polygon;

	polygon.clear();
	polygon.push_back(glm::vec3(512, 756, 0));
	polygon.push_back(glm::vec3(589, 756, 0));
	polygon.push_back(glm::vec3(850, 380, 0));
	polygon.push_back(glm::vec3(822, 340, 0));
	polygon.push_back(glm::vec3(275, 340, 0));
	polygon.push_back(glm::vec3(250, 380, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 1)));

	polygon.clear();
	polygon.push_back(glm::vec3(487, 797, 0));
	polygon.push_back(glm::vec3(612, 797, 0));
	polygon.push_back(glm::vec3(903, 380, 0));
	polygon.push_back(glm::vec3(844, 296, 0));
	polygon.push_back(glm::vec3(253, 296, 0));
	polygon.push_back(glm::vec3(201, 379, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.98, 0.53, 0.24, 1)));



	polygon.clear();
	polygon.push_back(glm::vec3(892, 507, 0));
	polygon.push_back(glm::vec3(942, 507, 0));
	polygon.push_back(glm::vec3(1000, 370, 0));
	polygon.push_back(glm::vec3(1000, 355, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.8), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(159, 507, 0));
	polygon.push_back(glm::vec3(207, 507, 0));
	polygon.push_back(glm::vec3(103, 353, 0));
	polygon.push_back(glm::vec3(103, 372, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.8), Region::Effect::Fill));


	polygon.clear();
	polygon.push_back(glm::vec3(657, 870, 0));
	polygon.push_back(glm::vec3(706, 870, 0));
	polygon.push_back(glm::vec3(763, 736, 0));
	polygon.push_back(glm::vec3(763, 722, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.8), Region::Effect::Fill));




	polygon.clear();
	polygon.push_back(glm::vec3(549, 668, 0));
	polygon.push_back(glm::vec3(695, 458, 0));
	polygon.push_back(glm::vec3(402, 458, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.4), Region::Effect::GradientRamp));



	polygon.clear();
	polygon.push_back(glm::vec3(652, 984, 0));
	polygon.push_back(glm::vec3(729, 984, 0));
	polygon.push_back(glm::vec3(737, 979, 0));
	polygon.push_back(glm::vec3(729, 972, 0));
	polygon.push_back(glm::vec3(652, 972, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.8), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(652 - 600, 984 - 670, 0));
	polygon.push_back(glm::vec3(729 - 600, 984 - 670, 0));
	polygon.push_back(glm::vec3(737 - 600, 979 - 670, 0));
	polygon.push_back(glm::vec3(729 - 600, 972 - 670, 0));
	polygon.push_back(glm::vec3(652 - 600, 972 - 670, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.8), Region::Effect::Fill));


	polygon.clear();
	polygon.push_back(glm::vec3(411, 330, 0));
	polygon.push_back(glm::vec3(525, 330, 0));
	polygon.push_back(glm::vec3(562, 296, 0));
	polygon.push_back(glm::vec3(377, 296, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.5), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(354, 246, 0));
	polygon.push_back(glm::vec3(360, 246, 0));
	polygon.push_back(glm::vec3(360, 236, 0));
	polygon.push_back(glm::vec3(354, 236, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 1), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(280, 282, 0));
	polygon.push_back(glm::vec3(357, 282, 0));
	polygon.push_back(glm::vec3(379, 261, 0));
	polygon.push_back(glm::vec3(259, 261, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.3), Region::Effect::Fill));


	polygon.clear();
	polygon.push_back(glm::vec3(281, 272, 0));
	polygon.push_back(glm::vec3(321, 272, 0));
	polygon.push_back(glm::vec3(334, 261, 0));
	polygon.push_back(glm::vec3(269, 261, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.3), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(281 + 65, 272, 0));
	polygon.push_back(glm::vec3(321 + 65, 272, 0));
	polygon.push_back(glm::vec3(334 + 65, 261, 0));
	polygon.push_back(glm::vec3(269 + 65, 261, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.3), Region::Effect::Fill));

	polygon.clear();
	polygon.push_back(glm::vec3(247, 508, 0));
	polygon.push_back(glm::vec3(380, 695, 0));
	polygon.push_back(glm::vec3(382, 677, 0));
	polygon.push_back(glm::vec3(267, 512, 0));
	renders.push_back(new Region(polygon, glm::vec4(0.30, 0.75, 0.98, 0.3), Region::Effect::Fill));

}


void CreateCurves(std::list<IRenderable *>& renders)
{
	std::vector<glm::vec3> points;
	std::vector<glm::vec4> colors;

	points.clear();
	points.push_back(glm::vec3(466, 845, 0));
	points.push_back(glm::vec3(635, 845, 0));
	points.push_back(glm::vec3(957, 378, 0));
	points.push_back(glm::vec3(870, 250, 0));
	points.push_back(glm::vec3(229, 250, 0));
	points.push_back(glm::vec3(140, 378, 0));
	points.push_back(glm::vec3(466, 845, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.98, 1.0)));


	points.clear();
	points.push_back(glm::vec3(476, 835, 0));
	points.push_back(glm::vec3(625, 835, 0));
	points.push_back(glm::vec3(944, 378, 0));
	points.push_back(glm::vec3(860, 260, 0));
	points.push_back(glm::vec3(238, 260, 0));
	points.push_back(glm::vec3(154, 378, 0));
	points.push_back(glm::vec3(476, 835, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.98,1.0),5));

	points.clear();
	points.push_back(glm::vec3(361, 161, 0));
	points.push_back(glm::vec3(361, 95, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78,1.0), 12));

	int heights[] = { 25,40,35,30,60,25,70,30 };
	int intevalX = 20;
	for (int i = 0; i < 8; i++)
	{
		int h = heights[i];
		points.clear();
		points.push_back(glm::vec3(382+ intevalX*i, 161, 0));
		points.push_back(glm::vec3(382+ intevalX*i, 161-h, 0));
		colors.clear();
		colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
		colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
		renders.push_back(new Curve(points, colors, 15));
	}


	points.clear();
	points.push_back(glm::vec3(162, 852, 0));
	points.push_back(glm::vec3(162, 825, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));

	points.clear();
	points.push_back(glm::vec3(179, 859, 0));
	points.push_back(glm::vec3(179, 859-35, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));

	points.clear();
	points.push_back(glm::vec3(200, 840, 0));
	points.push_back(glm::vec3(200, 840 - 60, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));


	points.clear();
	points.push_back(glm::vec3(759, 244, 0));
	points.push_back(glm::vec3(759, 244-25, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));

	points.clear();
	points.push_back(glm::vec3(778, 244, 0));
	points.push_back(glm::vec3(778, 244 - 60, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));

	points.clear();
	points.push_back(glm::vec3(819, 244, 0));
	points.push_back(glm::vec3(819, 244 - 35, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));

	points.clear();
	points.push_back(glm::vec3(859, 244, 0));
	points.push_back(glm::vec3(859, 244 - 15, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 15));


	points.clear();
	points.push_back(glm::vec3(508, 242, 0));
	points.push_back(glm::vec3(508-85, 242, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 5));

	points.clear();
	points.push_back(glm::vec3(531, 242, 0));
	points.push_back(glm::vec3(531 + 85, 242, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 5));

	points.clear();
	points.push_back(glm::vec3(515, 242, 0));
	points.push_back(glm::vec3(525, 242, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	renders.push_back(new Curve(points, colors, 5));


	points.clear();
	points.push_back(glm::vec3(476, 871, 0));
	points.push_back(glm::vec3(476 - 60, 871, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 13));

	points.clear();
	points.push_back(glm::vec3(495, 871, 0));
	points.push_back(glm::vec3(495 + 60, 871, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 13));

	points.clear();
	points.push_back(glm::vec3(480, 871, 0));
	points.push_back(glm::vec3(490, 871, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	renders.push_back(new Curve(points, colors, 13));


	points.clear();
	points.push_back(glm::vec3(476, 887, 0));
	points.push_back(glm::vec3(476 - 60, 887, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 3));

	points.clear();
	points.push_back(glm::vec3(495, 887, 0));
	points.push_back(glm::vec3(495 + 60, 887, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0.0));
	renders.push_back(new Curve(points, colors, 3));

	points.clear();
	points.push_back(glm::vec3(480, 887, 0));
	points.push_back(glm::vec3(490, 887, 0));
	colors.clear();
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1.0));
	renders.push_back(new Curve(points, colors, 3));
}


void CreateCircles(std::list<IRenderable *>& renders)
{
	float pi = 3.14159265358;
	renders.push_back(new Circle(glm::vec3(990, 291, 0), glm::vec3(0.30, 0.75, 0.78), 15, 105 * pi / 180, 255 * pi / 180));
	renders.push_back(new Circle(glm::vec3(990, 291, 0), glm::vec3(0.30, 0.75, 0.78), 15, 285 * pi / 180, 435 * pi / 180));
	renders.push_back(new Circle(glm::vec3(990, 291, 0), glm::vec3(0.30, 0.75, 0.78), 20, 15 * pi / 180, 165 * pi / 180));
	renders.push_back(new Circle(glm::vec3(990, 291, 0), glm::vec3(0.30, 0.75, 0.78), 20, 195 * pi / 180, 345 * pi / 180));

	renders.push_back(new Circle(glm::vec3(63, 518, 0), glm::vec3(0.30, 0.75, 0.78), 15, 105 * pi / 180, 255 * pi / 180));
	renders.push_back(new Circle(glm::vec3(63, 518, 0), glm::vec3(0.30, 0.75, 0.78), 15, 285 * pi / 180, 435 * pi / 180));
	renders.push_back(new Circle(glm::vec3(63, 518, 0), glm::vec3(0.30, 0.75, 0.78), 20, 15 * pi / 180, 165 * pi / 180));
	renders.push_back(new Circle(glm::vec3(63, 518, 0), glm::vec3(0.30, 0.75, 0.78), 20, 195 * pi / 180, 345 * pi / 180));


	renders.push_back(new Circle(glm::vec3(825, 707, 0), glm::vec3(0.30, 0.75, 0.78), 20, 15 * pi / 180, 165 * pi / 180));
	renders.push_back(new Circle(glm::vec3(825, 707, 0), glm::vec3(0.30, 0.75, 0.78), 20, 195 * pi / 180, 345 * pi / 180));
	renders.push_back(new Circle(glm::vec3(825, 707, 0), glm::vec3(0.30, 0.75, 0.78), 25, 105 * pi / 180, 255 * pi / 180));
	renders.push_back(new Circle(glm::vec3(825, 707, 0), glm::vec3(0.30, 0.75, 0.78), 25, 285 * pi / 180, 435 * pi / 180));

	renders.push_back(new Circle(glm::vec3(361, 198, 0), glm::vec3(0.30, 0.75, 0.78), 20, 15 * pi / 180, 165 * pi / 180));
	renders.push_back(new Circle(glm::vec3(361, 198, 0), glm::vec3(0.30, 0.75, 0.78), 20, 195 * pi / 180, 345 * pi / 180));
	renders.push_back(new Circle(glm::vec3(361, 198, 0), glm::vec3(0.30, 0.75, 0.78), 25, 105 * pi / 180, 255 * pi / 180));
	renders.push_back(new Circle(glm::vec3(361, 198, 0), glm::vec3(0.30, 0.75, 0.78), 25, 285 * pi / 180, 435 * pi / 180));

	renders.push_back(new Circle(glm::vec3(615, 978, 0), glm::vec3(0.30, 0.75, 0.78), 20, 15 * pi / 180, 165 * pi / 180));
	renders.push_back(new Circle(glm::vec3(615, 978, 0), glm::vec3(0.30, 0.75, 0.78), 20, 195 * pi / 180, 345 * pi / 180));
	renders.push_back(new Circle(glm::vec3(615, 978, 0), glm::vec3(0.30, 0.75, 0.78), 25, 105 * pi / 180, 255 * pi / 180));
	renders.push_back(new Circle(glm::vec3(615, 978, 0), glm::vec3(0.30, 0.75, 0.78), 25, 285 * pi / 180, 435 * pi / 180));

	renders.push_back(new Circle(glm::vec3(96, 209, 0), glm::vec3(0.30, 0.75, 0.78), 26));
	renders.push_back(new Circle(glm::vec3(52, 542, 0), glm::vec3(0.30, 0.75, 0.78), 26));

}

void CreateProcessBars(std::list<IRenderable *>& renders)
{
	renders.push_back(new ProcessBar(glm::vec4(991, 162, 20, 6)));
	renders.push_back(new ProcessBar(glm::vec4(152, 46, 25, 6)));
	renders.push_back(new ProcessBar(glm::vec4(55, 205, 18, 8)));
	renders.push_back(new ProcessBar(glm::vec4(125, 205, 18, 8)));
	renders.push_back(new ProcessBar(glm::vec4(86, 244, 25, 6)));
	renders.push_back(new ProcessBar(glm::vec4(171, 515, 25, 6)));

	renders.push_back(new ProcessBar(glm::vec4(394, 936, 4, 16), ProcessBar::Direction::Vertical));
	renders.push_back(new ProcessBar(glm::vec4(112, 88, 8, 12), ProcessBar::Direction::Vertical));
}


std::wstring s2ws(const std::string& str)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}
void CreatePanel0(std::list<IRenderable *>& renders)
{
	std::vector<glm::vec3> points;
	std::vector<glm::vec4> colors;

	points.clear();
	points.push_back(glm::vec3(985, 109, 0));
	points.push_back(glm::vec3(985, 133, 0));
	points.push_back(glm::vec3(1022, 133, 0));
	points.push_back(glm::vec3(1022, 109, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(737, 294, 0));
	points.push_back(glm::vec3(747, 316, 0));
	points.push_back(glm::vec3(839, 315, 0));
	points.push_back(glm::vec3(953, 152, 0));
	points.push_back(glm::vec3(1020, 152, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(991, 129, 0));
	points.push_back(glm::vec3(991, 120, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(995, 121, 0));
	points.push_back(glm::vec3(1002, 121, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(995, 127, 0));
	points.push_back(glm::vec3(1002, 127, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));


	points.clear();
	points.push_back(glm::vec3(958, 196, 0));
	points.push_back(glm::vec3(958, 220, 0));
	points.push_back(glm::vec3(981, 220, 0));
	points.push_back(glm::vec3(981, 196, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(945, 195, 0));
	points.push_back(glm::vec3(950, 195, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));

	points.clear();
	points.push_back(glm::vec3(941, 200, 0));
	points.push_back(glm::vec3(951, 200, 0));
	renders.push_back(new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));







	//CurveParameter curveParameter = CurveSerializer::Load("curve");
	
	for (auto& p : std::experimental::filesystem::directory_iterator("./demos/demo002/curves"))
	{
		std::wstring wstr = p.path();
		std::string str = ws2s(wstr);
		CurveParameter curveParameter = CurveSerializer::Load(str.c_str());
		renders.push_back(new Curve(curveParameter.points, glm::vec4(0.30, 0.75, 0.78, 1.0), 1.8));
	}
	//std::experimental::filesystem::cre
}

void CreateTest(std::list<IRenderable *>& renders)
{
	Point *point = new Point(glm::vec3(353, 982, 0), glm::vec3(0.30, 0.75, 0.78), Point::Type::Polygon);
	renders.push_back(point);

	point = new Point(glm::vec3(213, 93, 0), glm::vec3(0.30, 0.75, 0.78), Point::Type::Polygon);
	point->angle = -pi<float>() / 2;
	renders.push_back(point);
	
}

void CreateTheLast(std::list<IRenderable *>& renders)
{
	float pi = 3.14159265358;
	Point *point = new Point(glm::vec3(392, 971, 0), glm::vec4(0.30, 0.75, 0.78, 1.0), Point::Type::Polygon);
	point->angle = pi / 4;
	point->segment = 4;
	point->size = 12;
	renders.push_back(point);

	point = new Point(glm::vec3(203, 53, 0), glm::vec4(0.30, 0.75, 0.78, 1.0), Point::Type::Polygon);
	point->angle = pi / 4;
	point->segment = 4;
	point->size = 12;
	renders.push_back(point);


	point = new Point(glm::vec3(89, 213, 0), glm::vec4(0.30, 0.75, 0.78, 1.0), Point::Type::Polygon);
	point->angle = pi / 4;
	point->segment = 4;
	point->size = 20;
	renders.push_back(point);

}

int main(void)
{
	Engine engine(1100,1100);

	engine.uilist.push_back(new Command(&engine));

	//engine.uilist.push_back(new Background());
	//engine.uilist.push_back(new Image("images/fake002.dds", Screen::width / 2, 0, Screen::width / 2, Screen::height, glm::vec4(1, 1, 1, 1)));
	CreateBackPoints(engine.uilist);
	CreateBackgroundRects(engine.uilist);
	CreatePolygons(engine.uilist);
	CreateCurves(engine.uilist);
	CreateCircles(engine.uilist);
	CreateProcessBars(engine.uilist);
	CreatePanel0(engine.uilist);
	CreateTest(engine.uilist);
	engine.uilist.push_back(new MaskedShapes());
	engine.uilist.push_back(new MaskedShapes2());
	engine.uilist.push_back(new ColumnDiagram(glm::vec4(418, 267, 425, 25)));
	CreateTheLast(engine.uilist);


	//engine.uilist.push_back(new ShowMousePosition());
	engine.uilist.push_back(new ShowFps());
	
	

	engine.Run();




	return 0;
}






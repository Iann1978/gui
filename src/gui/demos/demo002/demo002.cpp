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




#pragma warning (disable: 4996)



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




	renders.push_back(new ProcessBar(glm::vec4(991,162,20,6)));


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

int main(void)
{
	Engine engine(2200,1100);

	engine.uilist.push_back(new Command(&engine));

	engine.uilist.push_back(new Background());
	engine.uilist.push_back(new Image("images/fake002.dds", Screen::width / 2, 0, Screen::width / 2, Screen::height, glm::vec4(1, 1, 1, 1)));
	CreateBackPoints(engine.uilist);
	CreateBackgroundRects(engine.uilist);
	CreatePolygons(engine.uilist);
	CreateCurves(engine.uilist);
	CreateCircles(engine.uilist);
	CreatePanel0(engine.uilist);
	CreateTest(engine.uilist);
	engine.uilist.push_back(new MaskedShapes());


	engine.uilist.push_back(new ShowMousePosition());
	engine.uilist.push_back(new ShowFps());
	
	

	engine.Run();




	return 0;
}






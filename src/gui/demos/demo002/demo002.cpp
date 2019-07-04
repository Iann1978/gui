// Include standard headers
#include "prebuild.h"

#include <set>

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
#include <Engine/Region.h>
#include <Engine/Engine.h>


#include <StatusBar.h>


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
	glm::vec4 colors[] = { glm::vec4(0.08873602, 0.4435053, 0.752, 0.3), glm::vec4(0.694, 0.5205, 0.5205, 0.2) };
	float inteval = 1.0f * 1100 / 24;
	Region *region = new Region(glm::vec4(2*i*inteval/Screen::width-1, 2 * j*inteval / Screen::height - 1, 2 * inteval / Screen::width, 2 * inteval / Screen::height), colors[colorIndex]);
	return region;
}

void CreateBackgroundRects(std::list<IRenderable *>& renders)
{
	for (int j = 12; j < 24; j++)
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
	: Image("images/fake002.dds", 0, 0, Screen::width, Screen::height, glm::vec4(1, 1, 1, 0.4)) {}
void Background::Update()
{
	if (Input::GetKeyDown(Input::KeyCode::KeyQ))
	{
		color.a = (color.a == 0) ? 0.4 : 0;
	}
}
int main(void)
{
	Engine engine(1100,1100);

	//Image *image = new Image("images/fake002.dds", 0, 0, Screen::width, Screen::height,glm::vec4(1,1,1,0.4));
	engine.uilist.push_back(new Background());
	CreateBackPoints(engine.uilist);
	CreateBackgroundRects(engine.uilist);

	engine.Run();




	return 0;
}






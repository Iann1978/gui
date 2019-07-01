// Include standard headers
#include "prebuild.h"


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
int main(void)
{
	Engine engine(1100,1100);


	CreateBackPoints(engine.uilist);

	engine.Run();




	return 0;
}






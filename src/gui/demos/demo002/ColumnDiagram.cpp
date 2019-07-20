#include "prebuild.h"
#include "ColumnDiagram.h"
#include <Engine/Curve.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>
#include <Engine/Shader.h>
#include <Engine/Screen.h>
#include <Engine/Color.h>
#include <Engine/Region.h>

ColumnDiagram::ColumnDiagram(glm::vec4 rect)
{
	float interval = 8;
	for (float value = 0; value < rect.z; value += interval)
	{
		float x = rect.x + value;
		float y = rect.y + rect.w;
		float h = 2 + rand() % ((int)rect.w - 2);
		//Curve *curve = new Curve()
		std::vector<glm::vec3> points;
		points.push_back(glm::vec3(x, y, 0));
		points.push_back(glm::vec3(x, y-h, 0));
		Curve *curve = new Curve(points, glm::vec4(0.30, 0.75, 0.78, 1.0), 4);
		//Region *region = new Region(glm::vec4(rect.x + value, rect.y, 5, rect.w), glm::vec4(0.30, 0.75, 0.78, 1));
		fills.push_back(curve);
	}
}


ColumnDiagram::~ColumnDiagram()
{
	
}

void ColumnDiagram::Render()
{
	for (auto region : fills)
	{
		region->Render();
	}
}

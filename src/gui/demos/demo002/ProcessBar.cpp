#include "prebuild.h"
#include "ProcessBar.h"
#include <Engine/Region.h>
#include <Engine/Color.h>


ProcessBar::ProcessBar(glm::vec4 rect, Direction direction)
{
	this->rect = rect;
	this->direction = direction;

	float interval = 3;
	for (float value = 0; value < rect.z; value += interval)
	{
		Region *region = new Region(glm::vec4(rect.x + value, rect.y, 1.2, rect.w), glm::vec4(0.30, 0.75, 0.78,1));
		fills.push_back(region);
	}
}


ProcessBar::~ProcessBar()
{
}


void ProcessBar::Render()
{
	for (Region *region : fills)
	{
		region->Render();
	}
}
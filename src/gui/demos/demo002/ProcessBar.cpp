#include "prebuild.h"
#include "ProcessBar.h"
#include <Engine/Region.h>
#include <Engine/Color.h>
namespace demo002
{

	ProcessBar::ProcessBar(glm::vec4 rect, Direction direction)
	{
		this->rect = rect;
		this->direction = direction;

		if (direction == Direction::Horizontal)
		{
			float interval = 3;
			for (float value = 0; value < rect.z; value += interval)
			{
				Region *region = new Region(glm::vec4(rect.x + value, rect.y, 1.2, rect.w), glm::vec4(0.30, 0.75, 0.78, 1));
				fills.push_back(region);
			}
		}
		else if (direction == Direction::Vertical)
		{
			float interval = 3;
			for (float value = 0; value < rect.w; value += interval)
			{
				Region *region = new Region(glm::vec4(rect.x, rect.y + value, rect.z, 1.2), glm::vec4(0.30, 0.75, 0.78, 1));
				fills.push_back(region);
			}
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
}
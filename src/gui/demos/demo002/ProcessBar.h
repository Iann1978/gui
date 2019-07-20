#pragma once

#include <Engine/Renderable.h>

#include <vector>

class Region;
namespace demo002
{
	class ProcessBar : public IRenderable
	{
	public:
		enum Direction
		{
			Horizontal,
			Vertical,
		};
		Direction direction;
		glm::vec4 rect;
		std::vector<Region *> fills;

	public:
		ProcessBar(glm::vec4 rect, Direction direction = Horizontal);
		~ProcessBar();

	public:
		void Update() {};
		void Render();
	};
}

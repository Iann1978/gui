#pragma once
#include <Engine/Renderable.h>

class Curve;
class Mesh;
class Material;
class Region;

namespace demo002
{
	class ColumnDiagram : public IRenderable
	{

		std::vector<Curve *> fills;
	public:
		ColumnDiagram(glm::vec4 rect);
		~ColumnDiagram();

	public:
		void Update() {};
		void Render();


	};
}



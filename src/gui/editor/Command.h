#pragma once
#include <Engine/Renderable.h>

class Curve;
class Engine;
class Command : public IRenderable
{
	Engine *engine = nullptr;
	Curve *curve = nullptr;
	std::vector<glm::vec3> points;
public:
	Command(Engine *engine);
	~Command();

	void Update();
	void Render();
};


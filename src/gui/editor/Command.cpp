#include "prebuild.h"
#include "Command.h"

#include <Engine/Engine.h>
#include <Engine/Input.h>
#include <Engine/Curve.h>

Command::Command(Engine *engine)
{
	this->engine = engine;
}


Command::~Command()
{
}


void Command::Update()
{
	if (Input::GetKeyDown(Input::KeyCode::KeyA))
	{
		if (curve)
		{
			engine->uilist.push_back(curve);
			curve = nullptr;
		}
		points.clear();
	}

	if (Input::GetKeyDown(Input::KeyCode::LeftButton))
	{
		points.push_back(glm::vec3(Input::mousePosX, Input::mousePosY, 0));
		
	}

	if (curve)
	{
		delete curve;
		curve = nullptr;
	}

	if (points.size() >= 2)
	{
		curve = new Curve(points);
	}
}

void Command::Render()
{
	if (curve)
	{
		curve->Render();
	}

}
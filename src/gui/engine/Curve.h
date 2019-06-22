#pragma once
#include <Engine/Renderable.h>


class Curve : public IRenderable
{
	GLuint shader;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;

public:
	Curve();
	~Curve();

	void Update();
	void Render();
};


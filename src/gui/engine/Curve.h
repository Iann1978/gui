#pragma once
#include <Engine/Renderable.h>



class Curve : public IRenderable
{
	GLuint program;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;
	int pointNumber;

public:
	Curve(int pointNumber, float *vertexBufferData, float *colorBufferData);
	~Curve();

	void Update();
	void Render();
};


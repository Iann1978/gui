#pragma once
#include <Engine/Renderable.h>



class Point : public IRenderable
{
	GLuint program;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;
	int pointNumber;
	glm::vec3 position;
	glm::vec3 color;

public:
	Point(glm::vec3 position, glm::vec3 color);
	~Point();

	void Update();
	void Render();
};


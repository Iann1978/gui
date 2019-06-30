#pragma once
#include <Engine/Renderable.h>



class Point : public IRenderable
{
public:
	enum Type {
		Normal,
		Star,
	};
	Type type;
	GLuint program;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;
	glm::vec3 position;
	glm::vec3 color;

public:
	Point(glm::vec3 position, glm::vec3 color, Type type = Normal);
	~Point();

	void Update();
	void Render();

	void LoadNormal(glm::vec3 position, glm::vec3 color);
	void RenderNormal();

	void LoadStar(glm::vec3 position, glm::vec3 color);
	void RenderStar();
};


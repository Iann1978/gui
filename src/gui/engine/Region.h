#pragma once
#include <Engine/Renderable.h>

#include <vector>

class Region : public IRenderable
{
public:
	enum Type {
		Rect,
		Polygon
	};

	Type type;
	GLuint program;
	GLuint vertexbuffer;
	GLuint elementbuffer;
	GLuint elementsize;
	GLuint mainColorId;

	glm::vec4 rect;
	glm::vec4 color;

public:
	Region(glm::vec4 rect, glm::vec4 color);
	Region(std::vector<glm::vec3> polygon, glm::vec4 color);
	~Region();

	void Update();
	void Render();

	void LoadRect(glm::vec4 rect, glm::vec4 color);
	void RenderRect();

	void LoadPolygon(std::vector<glm::vec3> polygon);
	void RenderPolygon();


};


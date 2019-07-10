#pragma once
#include <Engine/Renderable.h>

#include <vector>

class Mesh;
class Region : public IRenderable
{
public:
	enum Type {
		Rect,
		Polygon
	};

	Type type;
	Mesh *mesh;
	GLuint program;
	GLuint mainColorId;
	GLuint screenWidthID;
	GLuint screenHeightID;

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


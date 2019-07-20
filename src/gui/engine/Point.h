#pragma once
#include <Engine/Renderable.h>


class Mesh;
class Material;
class Point : public IRenderable
{
public:
	enum Type {
		Normal,
		Star,
		Cross,
		Polygon,
	};
	Type type;
	Mesh *mesh;
	Material *material;
	
	glm::vec3 position;
	glm::vec3 color;
	float size = 18;
	float angle = 0;
	int segment = 3;

public:
	Point(glm::vec3 position, glm::vec3 color, Type type = Normal);
	~Point();

	void Update();
	void Render();

	void LoadNormal(glm::vec3 position, glm::vec3 color);
	void RenderNormal();

	void LoadStar(glm::vec3 position, glm::vec3 color);
	void RenderStar();
	
	void LoadCross(glm::vec3 position, glm::vec3 color);
	void RenderCross();

	void LoadPolygon(glm::vec3 position, glm::vec3 color);
	void RenderPolygon();
};


#pragma once
#include <Engine/Renderable.h>
#include <Engine/Color.h>

class Mesh;
class Material;
class Circle : public IRenderable
{
public:
	enum Type {

		Normal,
	};
	Type type;
	Mesh *mesh;
	Material *material;
	//GLuint program;
	//GLuint vertexbuffer;
	//GLuint colorbuffer;
	//GLuint screenWidthID;
	//GLuint screenHeightID;
	//GLuint centerColorID;
	//GLuint radiusID;
	//GLuint startAngleID;
	//GLuint endAngleID;
	float  radius;
	float  width = 2;
	float  startAngle;
	float  endAngle;
	glm::vec3 position;
	glm::vec3 color;

public:
	Circle(glm::vec3 position, glm::vec3 color = Color::white, float radius=20, float startAngle = 0, float endAngle = 2*glm::pi<float>() );
	~Circle();

	void Update();
	void Render();



	void LoadCross(glm::vec3 position, glm::vec3 color);
	void RenderCross();
};


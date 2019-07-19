#pragma once
#include <Engine/Renderable.h>
#include <Engine/Color.h>
#include <vector>

class Mesh;
class Curve : public IRenderable
{
	GLuint program;
	Mesh *mesh;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;
	GLuint widthID;
	int pointNumber;
	float width = 1;

public:
	Curve(int pointNumber, float *vertexBufferData, float *colorBufferData);
	Curve(std::vector<glm::vec3> points, glm::vec4 color = Color::white, float width = 1);
	Curve(std::vector<glm::vec3> points, std::vector<glm::vec4> colors, float width = 1);
	~Curve();

	void Update();
	void Render();

private:
	void LoadMesh(int pointNumber, float *vertexBufferData, float *colorBufferData);
	void LoadMaterial();
};


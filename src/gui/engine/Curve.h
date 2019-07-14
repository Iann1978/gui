#pragma once
#include <Engine/Renderable.h>

#include <vector>

class Curve : public IRenderable
{
	GLuint program;
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint screenWidthID;
	GLuint screenHeightID;
	GLuint widthID;
	int pointNumber;
	float width = 1;

public:
	Curve(int pointNumber, float *vertexBufferData, float *colorBufferData);
	Curve(std::vector<glm::vec3> curve, glm::vec3 color, float width = 1);
	~Curve();

	void Update();
	void Render();

private:
	void LoadMesh(int pointNumber, float *vertexBufferData, float *colorBufferData);
	void LoadMaterial();
};


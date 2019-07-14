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
	int pointNumber;

public:
	Curve(int pointNumber, float *vertexBufferData, float *colorBufferData);
	Curve(std::vector<glm::vec3> curve, glm::vec3 color);
	~Curve();

	void Update();
	void Render();

private:
	void LoadMesh(int pointNumber, float *vertexBufferData, float *colorBufferData);
	void LoadMaterial();
};


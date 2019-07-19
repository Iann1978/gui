#pragma once

class Mesh
{
public:
	enum Type
	{
		Triangles,
		Points,
	};
	Type type;
public:
	GLuint vertexbuffer = 0;
	GLuint uvbuffer = 0;
	GLuint colorbuffer = 0;
	GLuint elementbuffer = 0;
	GLuint elementsize = 0;
public:
	Mesh(const Mesh&) = delete;
	Mesh();
	Mesh(Type type, const int vertexBufferLength, const float* vertexBufferData,
		const int uvBufferLength, const float *uvBufferData, 
		const int colorBufferLength, const float *colorBufferData,
		const int elementBufferLength, const unsigned short *elementBufferData);
	~Mesh();

public:
	static Mesh *quad2;//rect(0,0,1,1)
	static Mesh *quad3;//rect(-1,-1,2,2)

	static void LoadPredefinedMeshes();
	static Mesh *CreateQuad(glm::vec4 rect);
	static Mesh *CreatePoint(glm::vec3 position, glm::vec4 color);
	static Mesh *CreatePolygon(std::vector<glm::vec3> points);
	static Mesh *CreateGradientMesh(glm::vec4 rect, glm::vec4 color0, glm::vec4 color1);
	static void RenderMesh(Mesh *mesh);
};


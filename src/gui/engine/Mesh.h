#pragma once

class Mesh
{
public:
	GLuint vertexbuffer = 0;
	GLuint uvbuffer = 0;
	GLuint colorbuffer = 0;
	GLuint elementbuffer = 0;
	GLuint elementsize = 0;
public:
	
	Mesh();
	Mesh(const int vertexBufferLength, const float* vertexBufferData,  const int uvBufferLength, const float *uvBufferData, const int elementBufferLength, const unsigned short *elementBufferData);
	~Mesh();

public:
	//static Mesh quad;
	static Mesh *quad2;
	static Mesh *quad3;
	static void LoadPredefinedMeshes();
	//static Mesh *CreateMesh(const int vertexBufferLength, const float* vertexBufferData, const int uvBufferLength, const float *uvBufferData, const int elementBufferLength, const unsigned short *elementBufferData);
	static Mesh *CreateMesh(glm::vec4 rect);
	static Mesh *CreateGradientMesh(glm::vec4 rect, glm::vec4 color0, glm::vec4 color1);
	//static Mesh quad0011;
	static void RenderMesh(Mesh *mesh);
};


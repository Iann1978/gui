#pragma once

class Mesh
{
public:
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint elementbuffer;
	GLuint elementsize;
public:
	
	//Mesh();
	Mesh(const int vertexBufferLength, const float* vertexBufferData,  const int uvBufferLength, const float *uvBufferData, const int elementBufferLength, const unsigned short *elementBufferData);
	~Mesh();

public:
	//static Mesh quad;
	static Mesh *quad2;
	static void LoadPredefinedMeshes();
	//static Mesh quad0011;
};


#include "prebuild.h"
#include "Mesh.h"



Mesh::Mesh(const int vertexBufferLength, const float* vertexBufferData, const int uvBufferLength, const float *uvBufferData, const int elementBufferLength, const unsigned short *elementBufferData)
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferLength * sizeof(float), vertexBufferData, GL_STATIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvBufferLength * sizeof(float), uvBufferData, GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBufferLength * sizeof(unsigned short), elementBufferData, GL_STATIC_DRAW);
	elementsize = elementBufferLength;
}


Mesh::~Mesh()
{
}


Mesh *Mesh::quad2 = nullptr;

void Mesh::LoadPredefinedMeshes()
{
	static const GLfloat quad2_vertexBufferData[] = {
	0.0f,0.0f,0.0f,
	0.0f,1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f,0.0f,0.0f,
	};

	static const GLfloat quad2_uvBufferData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	static const unsigned short quad2_elementBufferData[] = {
		0,1,2,0,2,3
	};
	quad2 = new Mesh(12, quad2_vertexBufferData, 8, quad2_uvBufferData, 6, quad2_elementBufferData);
}
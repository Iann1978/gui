#include "prebuild.h"
#include "Mesh.h"

static const GLfloat quad2_vertexBufferData[] = {
	0.0f,0.0f,0.0f,
	1.0f,0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	0.0f,1.0f,0.0f,
};

static const GLfloat quad2_uvBufferData[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

static const unsigned short quad2_elementBufferData[] = {
	0,1,2,0,2,3
};

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
Mesh *Mesh::quad3 = nullptr;

void Mesh::LoadPredefinedMeshes()
{
	
	quad2 = new Mesh(12, quad2_vertexBufferData, 8, quad2_uvBufferData, 6, quad2_elementBufferData);
	quad3 = CreateMesh(glm::vec4(-1, -1, 2, 2));
}

Mesh *Mesh::CreateMesh(glm::vec4 rect)
{
	float x = rect.x;
	float y = rect.y;
	float w = rect.z;
	float h = rect.w;

	float vertexBufferData[] = {
		x,		y,		0.0f,
		x + w,	y,		0.0f,
		x + w,	y + h,	0.0f,
		x,		y + h,	0.0f,
	};

	return new Mesh(12, vertexBufferData, 8, quad2_uvBufferData, 6, quad2_elementBufferData);
}


void Mesh::RenderMesh(Mesh *mesh)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
	glBindBuffer(GL_ARRAY_BUFFER, Mesh::quad2->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		mesh->elementsize,    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
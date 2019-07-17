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
Mesh::Mesh()
{

}
Mesh::Mesh(Type type, const int vertexBufferLength, const float* vertexBufferData,
	const int uvBufferLength, const float *uvBufferData, 
	const int colorBufferLength, const float *colorBufferData,
	const int elementBufferLength, const unsigned short *elementBufferData)
{
	this->type = type;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexBufferLength * sizeof(float), vertexBufferData, GL_STATIC_DRAW);

	if (uvBufferData)
	{
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvBufferLength * sizeof(float), uvBufferData, GL_STATIC_DRAW);
	}

	if (colorBufferData)
	{
		glGenBuffers(1, &colorbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, colorBufferLength * sizeof(float), colorBufferData, GL_STATIC_DRAW);
	}

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
	quad2 = CreateQuad(glm::vec4(0, 0, 1, 1));
	quad3 = CreateQuad(glm::vec4(-1, -1, 2, 2));
}

Mesh *Mesh::CreateQuad(glm::vec4 rect)
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

	return new Mesh(Triangles, 12, vertexBufferData,
		8, quad2_uvBufferData,
		0, nullptr,
		6, quad2_elementBufferData);
}

Mesh *Mesh::CreatePoint(glm::vec3 position, glm::vec4 color)
{
	return new Mesh(Points, 3, &position.x,
		0, nullptr,
		4, &color.x,
		0, nullptr);
}

Mesh *Mesh::CreateGradientMesh(glm::vec4 rect, glm::vec4 color0, glm::vec4 color1)
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


	float vertexColorData[] = {
		color0.r, color0.g,color0.b,color0.a,
		color0.r, color0.g,color0.b,color0.a,
		color1.r, color1.g,color1.b,color1.a,
		color1.r, color1.g,color1.b,color1.a,
	};

	return new Mesh(Triangles, 12, vertexBufferData,
		0, nullptr,
		16, vertexColorData,		
		6, quad2_elementBufferData);
}

void RenderTrianglesMesh(Mesh *mesh)
{
	if (mesh->type != Mesh::Type::Triangles)
	{
		printf("Error in RenderMeshTrianglesMesh");
		return;
	}

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

	if (mesh->uvbuffer)
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}


	if (mesh->colorbuffer)
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(2);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->colorbuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}

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
	glDisableVertexAttribArray(2);
}


void RenderPointsMesh(Mesh *mesh)
{
	if (mesh->type != Mesh::Type::Points)
	{
		printf("Error in RenderMeshPointsMesh");
		return;
	}

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

	if (mesh->uvbuffer)
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}


	if (mesh->colorbuffer)
	{
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(2);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->colorbuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			4,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}

	glDrawArrays(GL_POINTS, 0, 1);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
void Mesh::RenderMesh(Mesh *mesh)
{
	if (mesh->type == Type::Triangles)
		RenderTrianglesMesh(mesh);
	else if (mesh->type == Type::Points)
		RenderPointsMesh(mesh);
	else
		printf("Error in Mesh::RenderMesh().");
	
}
#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Region.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>

#include <vector>
extern "C"
{
#include "../../ext/triangle/triangle.h"
}




Region::Region(glm::vec4 rect, glm::vec4 color)
{
	this->type = Rect;
	this->rect = rect;
	this->color = color;
	LoadRect(rect, color);
}

Region::Region(std::vector<glm::vec3> polygon, glm::vec4 color)
{
	this->type = Polygon;
	this->color = color;
	LoadPolygon(polygon);
}


Region::~Region()
{
	glDeleteBuffers(1, &vertexbuffer);
}

void Region::Render()
{
	switch (type)
	{
	case Rect: RenderRect(); break;
	case Polygon: RenderPolygon(); break;
	default: printf("Error in Region::Render");
	}
}

void Region::Update()
{

}


void Region::LoadRect(glm::vec4 rect, glm::vec4 color)
{
	this->rect = rect;
	this->color = color;
	Shader *shader = Shader::Find("Region");
	program = shader->program;

	mainColorId = glGetUniformLocation(program, "mainColor");


	float x = rect.x;
	float y = rect.y;
	float w = rect.z;
	float h = rect.w;

	float vertexBufferData[] = {
		x,		y,		0.0f,
		x + w,	y,		0.0f,
		x + w,	y + h,	0.0f,
		x,		y,		0.0f,
		x + w,	y + h,	0.0f,
		x,		y + h,	0.0f,
	};

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertexBufferData, GL_STATIC_DRAW);
}
void Region::RenderRect()
{
	glUseProgram(program);


	glUniform4fv(mainColorId, 1, &color.x);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Region::LoadPolygon(std::vector<glm::vec3> polygon)
{
	//std::vector<glm::vec2> points;
	//points.push_back(glm::vec2(0, 0));
	//points.push_back(glm::vec2(1, 0));
	//points.push_back(glm::vec2(1, 1));
	//points.push_back(glm::vec2(0, 1));



	struct triangulateio in, out;
	in.numberofpoints = polygon.size();
	in.numberofpointattributes = 1;
	in.pointlist = (REAL *)malloc(in.numberofpoints * 2 * sizeof(REAL));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointlist[2 * i] = polygon[i].x;
		in.pointlist[2 * i + 1] = polygon[i].y;
	}
	in.pointmarkerlist = (int *)malloc(in.numberofpoints * sizeof(int));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointmarkerlist[i] = 1;
	}
	in.pointattributelist = (REAL *)malloc(in.numberofpoints *
		in.numberofpointattributes *
		sizeof(REAL));
	for (size_t i = 0; i < in.numberofpoints; i++)
	{
		in.pointattributelist[i] = 10;
	}

	in.numberofsegments = in.numberofpoints;
	in.segmentlist = (int*)malloc(in.numberofpoints * 2 * sizeof(int));

	for (size_t i = 0; i < in.numberofsegments; i++)
	{
		if (i == in.numberofsegments - 1)
		{
			in.segmentlist[2 * i] = i;
			in.segmentlist[2 * i + 1] = 0;
		}
		else
		{
			in.segmentlist[2 * i] = i;
			in.segmentlist[2 * i + 1] = i + 1;
		}
	}
	in.segmentmarkerlist = (int*)malloc(in.numberofsegments * sizeof(int));
	for (size_t i = 0; i < in.numberofsegments; i++)
	{
		in.segmentmarkerlist[i] = 1;
	}

	in.numberofholes = 0;
	in.numberofregions = 0;

	out.pointlist = (REAL *)NULL;            /* Not needed if -N switch used. */
											 /* Not needed if -N switch used or number of point attributes is zero: */
	out.pointattributelist = (REAL *)NULL;
	out.pointmarkerlist = (int *)NULL; /* Not needed if -N or -B switch used. */
	out.trianglelist = (int *)NULL;          /* Not needed if -E switch used. */
											 /* Not needed if -E switch used or number of triangle attributes is zero: */
	out.triangleattributelist = (REAL *)NULL;
	out.neighborlist = (int *)NULL;         /* Needed only if -n switch used. */
											/* Needed only if segments are output (-p or -c) and -P not used: */
	out.segmentlist = (int *)NULL;
	/* Needed only if segments are output (-p or -c) and -P and -B not used: */
	out.segmentmarkerlist = (int *)NULL;
	out.edgelist = (int *)NULL;             /* Needed only if -e switch used. */
	out.edgemarkerlist = (int *)NULL;   /* Needed if -e used and -B not used. */


	triangulate((char *)"pzAen", &in, &out, (struct triangulateio *) NULL);





	Shader *shader = Shader::Find("Region");
	program = shader->program;

	mainColorId = glGetUniformLocation(program, "mainColor");




	
	float *vertexBufferData = new float[out.numberofpoints * 3];
	for (int i = 0; i < out.numberofpoints; i++)
	{
		vertexBufferData[i * 3 + 0] = out.pointlist[i * 2 + 0];
		vertexBufferData[i * 3 + 1] = out.pointlist[i * 2 + 1];
		vertexBufferData[i * 3 + 2] = 0.1;
	}
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, out.numberofpoints * 3 * sizeof(float), vertexBufferData, GL_STATIC_DRAW);
	delete vertexBufferData;


	unsigned short *elementBufferData = new unsigned short[out.numberoftriangles * 3];
	for (int i = 0; i < out.numberoftriangles; i++)
	{
		elementBufferData[i * 3 + 0] = out.trianglelist[i * 3 + 0];
		elementBufferData[i * 3 + 1] = out.trianglelist[i * 3 + 1];
		elementBufferData[i * 3 + 2] = out.trianglelist[i * 3 + 2];
	}
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, out.numberoftriangles * 3 * sizeof(unsigned short), elementBufferData, GL_STATIC_DRAW);
	delete elementBufferData;
	elementsize = out.numberoftriangles * 3;

}
void Region::RenderPolygon()
{
	glUseProgram(program);


	glUniform4fv(mainColorId, 1, &color.x);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glDisable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	// Draw the triangle !
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		elementsize,    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

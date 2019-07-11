#include "prebuild.h"
#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Shader.h>
#include <Engine/Region.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Mesh.h>
#include <Engine/Color.h>
#include <Engine/FrameBuffer.h>


#include <vector>
extern "C"
{
#include "../../ext/triangle/triangle.h"
}




Region::Region(glm::vec4 rect, glm::vec4 color)
{
	this->type = Rect;
	this->effect = Fill;
	this->rect = rect;
	this->color = color;
	LoadRect(rect, color);
}

Region::Region(std::vector<glm::vec3> polygon, glm::vec4 color)
{
	this->type = Polygon;
	this->effect = FadeInEdge;
	this->color = color;
	LoadPolygon(polygon);
}


Region::~Region()
{
	//glDeleteBuffers(1, &vertexbuffer);
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
	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");


	mesh = Mesh::CreateMesh(rect);
}

void Region::RenderRect()
{
	glUseProgram(program);

	glUniform4fv(mainColorId, 1, &color.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Mesh::RenderMesh(mesh);
}

void Region::LoadPolygon(std::vector<glm::vec3> polygon)
{

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


	float *vertexBufferData = new float[out.numberofpoints * 3];
	for (int i = 0; i < out.numberofpoints; i++)
	{
		vertexBufferData[i * 3 + 0] = out.pointlist[i * 2 + 0];
		vertexBufferData[i * 3 + 1] = out.pointlist[i * 2 + 1];
		vertexBufferData[i * 3 + 2] = 0.1;
	}


	unsigned short *elementBufferData = new unsigned short[out.numberoftriangles * 3];
	for (int i = 0; i < out.numberoftriangles; i++)
	{
		elementBufferData[i * 3 + 0] = out.trianglelist[i * 3 + 0];
		elementBufferData[i * 3 + 1] = out.trianglelist[i * 3 + 1];
		elementBufferData[i * 3 + 2] = out.trianglelist[i * 3 + 2];
	}


	mesh = new Mesh(out.numberofpoints * 3, vertexBufferData, 0, nullptr, out.numberoftriangles * 3, elementBufferData);
	delete elementBufferData;
	delete vertexBufferData;






	framebuffer0 = new FrameBuffer();
	framebuffer1 = new FrameBuffer();

	LoadBasePass();
	LoadTemplatePass();
	LoadAddPass();

}
void Region::RenderPolygon()
{
	if (dirty)
	{


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		RenderBasePass(Color::black);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);



		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);



		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		RenderTemplatePass(framebuffer0->texture);

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		RenderTemplatePass(framebuffer1->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		//RenderTemplatePass(framebuffer0->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//RenderTemplatePass(framebuffer1->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		//RenderTemplatePass(framebuffer0->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//RenderTemplatePass(framebuffer1->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		//RenderTemplatePass(framebuffer0->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//RenderTemplatePass(framebuffer1->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer1->framebuffer);
		//RenderTemplatePass(framebuffer0->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer0->framebuffer);
		//RenderTemplatePass(framebuffer1->texture);

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//RenderTemplatePass(framebuffer0->texture);
		dirty = false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	RenderMaskPass();

	RenderAddPass(framebuffer1->texture);
}

void Region::LoadBasePass()
{

	Shader *shader = Shader::Find("Region");
	program = shader->program;

	mainColorId = glGetUniformLocation(program, "mainColor");
	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");

}
void Region::RenderBasePass(glm::vec4 color)
{
	glUseProgram(program);

	glUniform4fv(mainColorId, 1, &color.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	glDisable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	Mesh::RenderMesh(mesh);
}
void Region::RenderMaskPass()
{
	glUseProgram(program);

	glUniform4fv(mainColorId, 1, &Color::black0.x);
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO, GL_ONE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

	Mesh::RenderMesh(mesh);
}
void Region::LoadTemplatePass()
{
	Shader *shader = Shader::Find("Template");
	programOfTemplatePass = shader->program;


	baseWidthID = glGetUniformLocation(programOfTemplatePass, "baseWidth");
	baseHeightID = glGetUniformLocation(programOfTemplatePass, "baseHeight");
	templateWidthID = glGetUniformLocation(programOfTemplatePass, "templateWidth");
	templateHeightID = glGetUniformLocation(programOfTemplatePass, "templateHeight");
	baseTextureID = glGetUniformLocation(programOfTemplatePass, "baseTexture");
	templateTextureID = glGetUniformLocation(programOfTemplatePass, "templateTexture");

	//templateTexture = loadBMP_custom("images/template-white-5x5.bmp");
	templateTexture = generateGaussianTemplate();
}

void Region::RenderTemplatePass(GLuint texture)
{
	glUseProgram(programOfTemplatePass);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(baseTextureID, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, templateTexture);
	glUniform1i(templateTextureID, 1);

	glUniform1i(baseWidthID, Screen::width);
	glUniform1i(baseHeightID, Screen::height);
	glUniform1i(templateWidthID, 5);
	glUniform1i(templateHeightID, 5);



	glDisable(GL_BLEND);

	glBlendFunc(GL_ONE, GL_ZERO);
	glDisable(GL_DEPTH_TEST);

	Mesh::RenderMesh(Mesh::quad3);
}


void Region::LoadAddPass()
{
	Shader* shaderAdd = Shader::Find("ColorTexture");
	programOfAddPass = shaderAdd->program;
	baseTextureID_inAddPass = glGetUniformLocation(programOfAddPass, "baseTexture");
	colorID_inAddPass = glGetUniformLocation(programOfAddPass, "color");
}
void Region::RenderAddPass(GLuint texture)
{
	glUseProgram(programOfAddPass);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(baseTextureID_inAddPass, 0);
	glUniform4fv(colorID_inAddPass, 1, &Color::white.x);


	glEnable(GL_BLEND);

	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);
	glStencilMask(0x00);
	glStencilFunc(GL_EQUAL, 0xFF, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	Mesh::RenderMesh(Mesh::quad3);

	//glDisable(GL_STENCIL_TEST);

}
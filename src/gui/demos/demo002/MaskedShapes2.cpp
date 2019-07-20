#include "prebuild.h"
#include "MaskedShapes2.h"
#include <Engine/Curve.h>
#include <Engine/Mesh.h>
#include <Engine/Material.h>
#include <Engine/Shader.h>
#include <Engine/Screen.h>
#include <Engine/Color.h>
namespace demo002
{
	MaskedShapes2::MaskedShapes2()
	{
		LoadStencilPass();
		LoadGradientPass();

	}


	MaskedShapes2::~MaskedShapes2()
	{
	}

	void MaskedShapes2::Render()
	{
		ClearStencil();
		RenderStencilPass();
		RenderGradientPass();
	}

	void MaskedShapes2::ClearStencil()
	{
		glStencilMask(~0);
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
	}


	void MaskedShapes2::LoadStencilPass()
	{
		std::vector<glm::vec3> points;
		points.clear();
		points.push_back(glm::vec3(476, 835, 0));
		points.push_back(glm::vec3(625, 835, 0));
		points.push_back(glm::vec3(944, 378, 0));
		points.push_back(glm::vec3(860, 260, 0));
		points.push_back(glm::vec3(238, 260, 0));
		points.push_back(glm::vec3(154, 378, 0));
		stencilMesh = Mesh::CreatePolygon(points);

		Shader *shader = Shader::Find("Region");
		stencilMat = new Material(shader);
		stencilMat->SetFloat("screenWidth", Screen::width);
		stencilMat->SetFloat("screenHeight", Screen::height);
		stencilMat->SetVector("mainColor", Color::black0);
	}

	void MaskedShapes2::RenderStencilPass()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_NEVER);

		// Stencil status
		glEnable(GL_STENCIL_TEST);
		glStencilMask(~0);
		glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
		glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);


		glDisable(GL_BLEND);

		stencilMat->Use();
		Mesh::RenderMesh(stencilMesh);

	}

	void  MaskedShapes2::LoadGradientPass()
	{
		std::vector<glm::vec3> points;
		points.push_back(glm::vec3(764, 617, 0));
		points.push_back(glm::vec3(1090, 617, 0));

		std::vector<glm::vec4> colors;
		colors.push_back(glm::vec4(0.30, 0.75, 0.78, 1));
		colors.push_back(glm::vec4(0.30, 0.75, 0.78, 0));
		gradient = new Curve(points, colors, 15);

		points.clear();
		points.push_back(glm::vec3(330, 601, 0));
		points.push_back(glm::vec3(30, 601, 0));
		gradient1 = new Curve(points, colors, 15);

		points.clear();
		points.push_back(glm::vec3(330, 622, 0));
		points.push_back(glm::vec3(40, 622, 0));
		gradient2 = new Curve(points, colors, 15);

		points.clear();
		points.push_back(glm::vec3(370, 674, 0));
		points.push_back(glm::vec3(140, 674, 0));
		gradient3 = new Curve(points, colors, 15);

	}
	void  MaskedShapes2::RenderGradientPass()
	{
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_STENCIL_TEST);
		glStencilMask(0);
		glStencilFunc(GL_NOTEQUAL, 0xFF, ~0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gradient->material->Use();
		Mesh::RenderMesh(gradient->mesh);
		Mesh::RenderMesh(gradient1->mesh);
		Mesh::RenderMesh(gradient2->mesh);
		Mesh::RenderMesh(gradient3->mesh);

		//gradient->Render();
	}
}
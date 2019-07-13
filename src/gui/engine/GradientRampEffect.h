#pragma once
class Mesh;
class Shader;
class GradientRampEffect
{


public:
	GradientRampEffect(Mesh *mesh);
	~GradientRampEffect();

	void Render();

	// Gradient Pass
	Mesh *gradientMesh;
	Shader *gradientShader;
	GLuint mainColorId;
	GLuint screenWidthID;
	GLuint screenHeightID;
	void LoadGradientPass();
	void RenderGradientPass();

	// Stencil Pass
	Mesh *stencilMesh;
	Shader *stencilShader;
	void LoadStencilPass(Mesh *stencilMesh);
	void RenderStencilPass();
};


#pragma once
#include <Engine/Renderable.h>

class Curve;
class Mesh;
class Material;
class MaskedShapes : public IRenderable
{
public:
	MaskedShapes();
	~MaskedShapes();

public:
	void Update() {};
	void Render();

	void ClearStencil();

	Mesh *stencilMesh;
	Material *stencilMat;
	void LoadStencilPass();
	void RenderStencilPass();

	Curve *gradient;
	Curve *gradient1;
	Curve *gradient2;

	void LoadGradientPass();
	void RenderGradientPass();
};


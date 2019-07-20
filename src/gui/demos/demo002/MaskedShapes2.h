#pragma once
#include <Engine/Renderable.h>

class Curve;
class Mesh;
class Material;
namespace demo002
{
	class MaskedShapes2 : public IRenderable
	{
	public:
		MaskedShapes2();
		~MaskedShapes2();

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
		Curve *gradient3;

		void LoadGradientPass();
		void RenderGradientPass();
	};
}


#pragma once
#include <Engine/Renderable.h>

#include <vector>

class Mesh;
class FrameBuffer;
class EffectContainer;
class Region : public IRenderable
{
public:
	enum Type {
		Rect,
		Polygon
	};

	enum Effect {
		Fill,
		FadeInEdge,
	};
	EffectContainer *effectContainer = nullptr;

	Type type;
	Effect effect = Fill;
	Mesh *mesh = nullptr;
	GLuint program;
	GLuint mainColorId;
	GLuint screenWidthID;
	GLuint screenHeightID;

	glm::vec4 rect;
	glm::vec4 color;






public:
	Region(glm::vec4 rect, glm::vec4 color, Effect effect = Effect::Fill);
	Region(std::vector<glm::vec3> polygon, glm::vec4 color, Effect effect = Effect::FadeInEdge);
	~Region();

	void Update();
	void Render();

	void LoadRect(glm::vec4 rect, glm::vec4 color);
	void LoadPolygon(std::vector<glm::vec3> polygon);
	

	void RenderFill();
	void RenderFadeInEdge();

	


};


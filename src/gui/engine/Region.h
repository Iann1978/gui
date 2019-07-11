#pragma once
#include <Engine/Renderable.h>

#include <vector>

class Mesh;
class FrameBuffer;
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

	Type type;
	Effect effect = Fill;
	Mesh *mesh;
	GLuint program;
	GLuint mainColorId;
	GLuint screenWidthID;
	GLuint screenHeightID;

	glm::vec4 rect;
	glm::vec4 color;


	FrameBuffer *framebuffer0;
	FrameBuffer *framebuffer1;

	bool dirty = true;



public:
	Region(glm::vec4 rect, glm::vec4 color);
	Region(std::vector<glm::vec3> polygon, glm::vec4 color);
	~Region();

	void Update();
	void Render();

	void LoadRect(glm::vec4 rect, glm::vec4 color);
	void RenderRect();

	void LoadPolygon(std::vector<glm::vec3> polygon);
	void RenderPolygon();

	// Base pass
	void LoadBasePass();
	void RenderBasePass(glm::vec4 color);

	// Mask Pass
	void RenderMaskPass();


	// Template pass
	GLuint programOfTemplatePass;
	GLuint baseWidthID;
	GLuint baseHeightID;
	GLuint templateWidthID;
	GLuint templateHeightID;
	GLuint baseTextureID;
	GLuint templateTextureID;
	GLuint templateTexture;
	void LoadTemplatePass();
	void RenderTemplatePass(GLuint texture);

	// Add pass
	GLuint programOfAddPass;
	GLuint texture0ID_inAddPass;
	GLuint texture1ID_inAddPass;
	void LoadAddPass();
	void RenderAddPass(GLuint texture);
	// Effect



};


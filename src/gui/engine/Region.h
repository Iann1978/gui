#pragma once
#include <Engine/Renderable.h>



class Region : public IRenderable
{
public:
	enum Type {
		Rect,
	};

	Type type;
	GLuint program;
	GLuint vertexbuffer;
	GLuint mainColorId;

	glm::vec4 rect;
	glm::vec4 color;

public:
	Region(glm::vec4 rect, glm::vec4 color);
	~Region();

	void Update();
	void Render();


};


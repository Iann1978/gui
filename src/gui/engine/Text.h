#pragma once
#include <Engine/Renderable.h>

class Text : public IRenderable
{
	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	unsigned int Text2DShaderID;
	unsigned int Text2DUniformID;
	GLuint screenWidthID;
	GLuint screenHeightID;
	const char* text;
	int x, y;
	int fontSize;
public:
	void initText2D(const char* texturePath);
	void printText2D(const char* text, int x, int y, int size);
	void cleanupText2D();

public:
	Text(const char* text, int x, int y, int fontSize);
	~Text();

	void Update() {};
	void Render();
};


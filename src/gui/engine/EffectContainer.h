#pragma once
class FrameBuffer;
class Mesh;
class EffectContainer
{
	FrameBuffer *framebuffer0;
	FrameBuffer *framebuffer1;

	bool dirty = true;
public:
	EffectContainer(Mesh *mesh, glm::vec4 color);
	~EffectContainer();

	void Render();


	// Base pass
	Mesh *mesh;
	GLuint program;
	GLuint mainColorId;
	GLuint screenWidthID;
	GLuint screenHeightID;
	glm::vec4 color;
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
	GLuint templateColorScaleID;
	GLuint templateTexture;
	void LoadTemplatePass();
	void RenderTemplatePass(GLuint texture);

	// Add pass
	GLuint programOfAddPass;
	GLuint baseTextureID_inAddPass;
	GLuint colorID_inAddPass;
	void LoadAddPass();
	void RenderAddPass(GLuint texture);
};


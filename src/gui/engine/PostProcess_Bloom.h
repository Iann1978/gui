#pragma once
class PostProcess;
class PostProcess_Bloom
{
	PostProcess *process;
	GLuint texture;

	GLuint vertexbuffer;
	GLuint uvbuffer;

	// HBlur pass and VBlur pass
	GLuint program[2];
	GLuint textureID[2];
	GLuint screenWidthID[2];
	GLuint screenHeightID[2];

	// Add pass
	GLuint programOfAddPass;
	GLuint texture0ID_inAddPass;
	GLuint texture1ID_inAddPass;

	
public:
	PostProcess_Bloom(PostProcess *process);
	~PostProcess_Bloom();

	void RenderBlurPass();
	void RenderAddPass();
	void Render();
};


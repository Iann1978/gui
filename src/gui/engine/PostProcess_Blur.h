#pragma once
class PostProcess;
class PostProcess_Blur
{
	PostProcess *process;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	


	GLuint program[2];
	GLuint textureID[2];
	GLuint screenWidthID[2];
	GLuint screenHeightID[2];



public:

	PostProcess_Blur(PostProcess *process);
	~PostProcess_Blur();


	void Render();
	void RenderPass();
};


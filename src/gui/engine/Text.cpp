#include "prebuild.h"
#include <common/texture.hpp>
#include <common/common_shader.hpp>
#include <vector>
#include <Engine/Shader.h>
#include <Engine/Text.h>
#include <Engine/Screen.h>

Text::Text(const char* text, int x, int y, int fontSize)
{
	this->text = text;
	this->x = x;
	this->y = y;
	this->fontSize = fontSize;
	initText2D("images/Holstein.DDS");
}


Text::~Text()
{
	cleanupText2D();
}

void Text::initText2D(const char* texturePath) {

	// Initialize texture
	Text2DTextureID = loadDDS(texturePath);

	// Initialize VBO
	glGenBuffers(1, &Text2DVertexBufferID);
	glGenBuffers(1, &Text2DUVBufferID);

	// Initialize Shader
	//Text2DShaderID = LoadShaders("shaders/Text_vert.shader", "shaders/Text_frag.shader");
	Shader *shader = Shader::Find("Text");
	Text2DShaderID = shader->program;

	// Initialize uniforms' IDs
	Text2DUniformID = glGetUniformLocation(Text2DShaderID, "myTextureSampler");
	screenWidthID = glGetUniformLocation(Text2DShaderID, "screenWidth");
	screenHeightID = glGetUniformLocation(Text2DShaderID, "screenHeight");

}

void Text::printText2D(const char* text, int x, int y, int size) {

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
	for (unsigned int i = 0; i < length; i++) {

		glm::vec2 vertex_up_left = glm::vec2(x + i * size, y + size);
		glm::vec2 vertex_up_right = glm::vec2(x + i * size + size, y + size);
		glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
		glm::vec2 vertex_down_left = glm::vec2(x + i * size, y);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);

		char character = text[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = (character / 16) / 16.0f;

		glm::vec2 uv_up_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);
		glm::vec2 uv_down_left = glm::vec2(uv_x, uv_y);
		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Bind shader
	glUseProgram(Text2DShaderID);
	
	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);


	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Text2DTextureID);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Text2DUniformID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DVertexBufferID);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Text2DUVBufferID);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Text::cleanupText2D() {

	// Delete buffers
	glDeleteBuffers(1, &Text2DVertexBufferID);
	glDeleteBuffers(1, &Text2DUVBufferID);

	// Delete texture
	glDeleteTextures(1, &Text2DTextureID);

	// Delete shader
	glDeleteProgram(Text2DShaderID);
}

void Text::Render()
{
	//printText2D("BEIJING WEST MOUNT COMPOUNDI", 0, 0, 20);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	printText2D(text, x, y, fontSize);
}
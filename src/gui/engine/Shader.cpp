#include "prebuild.h"
#include "Shader.h"
#include <stdio.h>
#include <string.h>
#include <common/common_shader.hpp>
static std::map<std::string, Shader*> shaders;

Shader::Shader(const char *name, const char *vertexShaderFile, const char *fragmentShaderFile, const char *geometryShaderFile)
{
	strcpy_s(this->name, sizeof(this->name)-1, name);
	program = LoadShaders(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
	shaders.insert(std::pair<std::string, Shader*>(this->name, this));
}


Shader::~Shader()
{
	glDeleteProgram(program);
}

Shader *Shader::Find(const char *name)
{
	std::map<std::string, Shader*>::iterator it = shaders.find(name);
	if (it != shaders.end())
	{
		return it->second;
	}

	return nullptr;
}

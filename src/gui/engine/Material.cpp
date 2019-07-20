#include "prebuild.h"
#include "Material.h"


#include <Engine/Shader.h>
#include <Engine/Curve.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>


Material::Material(Shader *shader)
{
	this->shader = shader;
}


Material::~Material()
{
}

void Material::SetInt(const char *name, const int value)
{
	intValues[name] = value;
}
void Material::SetFloat(const char *name, const float value)
{
	floatValues[name] = value;
}
void Material::SetVector(const char *name, const glm::vec3 value)
{
	vec3Values[name] = value;
}
void Material::SetVector(const char *name, const glm::vec4 value)
{
	vec4Values[name] = value;
}
void Material::Use()
{
	glUseProgram(shader->program);
	for (auto i : intValues)
	{
		GLuint id = glGetUniformLocation(shader->program, i.first.c_str());
		glUniform1i(id, i.second);
	}

	for (auto i : floatValues)
	{
		GLuint id = glGetUniformLocation(shader->program, i.first.c_str());
		glUniform1f(id, i.second);
	}

	for (auto i : vec3Values)
	{
		GLuint id = glGetUniformLocation(shader->program, i.first.c_str());
		glUniform3f(id, i.second.x, i.second.y, i.second.z);
	}

	for (auto i : vec4Values)
	{
		GLuint id = glGetUniformLocation(shader->program, i.first.c_str());
		glUniform4f(id, i.second.x, i.second.y, i.second.z, i.second.w);
	}
}
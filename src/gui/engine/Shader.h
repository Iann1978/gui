#pragma once
#include <map>
class Shader
{
public:
	char name[512];
	GLuint program;
public:
	Shader(const char *name, const char *vertexShaderFile, const char *fragmentShaderFile, const char *geometryShaderFile=nullptr);
	~Shader();

	GLuint GetLocation(const char *valuename);
public:
	static Shader *Find(const char *name);

};


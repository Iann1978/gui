#pragma once
#include <map>
class Shader;
class Material
{
public:
	Shader *shader;

	std::map<std::string, float> floatValues;
	std::map<std::string, glm::vec3> vec3Values;
	
	
public:
	Material(Shader *shader);
	~Material();

public:
	void SetFloat(const char *name, const float value);
	void SetVector(const char *name, const glm::vec3 value);
	void Use();
};


#pragma once
#include <map>
class Shader;
class Material
{
public:
	Shader *shader;

	std::map<std::string, int> intValues;
	std::map<std::string, float> floatValues;
	std::map<std::string, glm::vec3> vec3Values;
	std::map<std::string, glm::vec4> vec4Values;
	
	
public:
	Material(Shader *shader);
	~Material();

public:
	void SetInt(const char *name, const int value);
	void SetFloat(const char *name, const float value);
	void SetVector(const char *name, const glm::vec3 value);
	void SetVector(const char *name, const glm::vec4 value);
	void Use();
};


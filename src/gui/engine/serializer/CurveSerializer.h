#pragma once

struct CurveParameter
{
	std::vector<glm::vec3> points;
};


class CurveSerializer
{
public:
	static CurveParameter Load(const char *filename);
	static void Save(const char *filename, const CurveParameter &param);
};


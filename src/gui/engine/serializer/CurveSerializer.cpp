#include "prebuild.h"
#include "CurveSerializer.h"
#include "../../ext/json/json.hpp"

#include <iostream>
#include <fstream>

using namespace nlohmann;

namespace glm
{
	using nlohmann::json;
	void to_json(json& j, const vec3& v) {
		j = json{ {"x", v.x}, {"y", v.y}, {"z", v.z} };
	}
	void from_json(const json& j, vec3& v) {
		j.at("x").get_to(v.x);
		j.at("y").get_to(v.y);
		j.at("z").get_to(v.z);
	}
}


CurveParameter CurveSerializer::Load(const char *filename)
{
	
	json j;
	std::ifstream is(filename);
	is >> j;
	is.close();

	
	CurveParameter param;
	param.points = j.get < std::vector<glm::vec3> >();
	
	return param;
}



namespace ns {
	// a simple struct to model a person
	struct person {
		std::string name;
		std::string address;
		int age;
	};
	void to_json(json& j, const person& p) {
		j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
	}

	void from_json(const json& j, person& p) {
		j.at("name").get_to(p.name);
		j.at("address").get_to(p.address);
		j.at("age").get_to(p.age);
	}
}
void CurveSerializer::Save(const char *filename, const CurveParameter &param)
{

	json j = param.points;



	std::ofstream myfile(filename);
	myfile << j;
	myfile.close();
}
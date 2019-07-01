#include <list>
class IRenderable;
class PostProcess;
class Engine
{
	glm::vec3 backgroundColor;
	PostProcess *postProcess = nullptr;
public:
	Engine(int width = 1920, int height = 1080);
	~Engine();

	
	void LoadAllShaders();
	void ReleaseAllShaders();
	void Run();
	

	std::list<IRenderable*> uilist;
	std::list<IRenderable*> geolist;


};
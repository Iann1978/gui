#include <list>
class IRenderable;
class Engine
{
public:
	Engine(int width = 1920, int height = 1080);
	~Engine();

	
	void LoadAllShaders();
	void ReleaseAllShaders();
	void Run();
	

	std::list<IRenderable*> uilist;
	std::list<IRenderable*> geolist;


};
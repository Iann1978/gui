class Engine
{
public:
	Engine();
	~Engine();

	
	void LoadAllShaders();
	void ReleaseAllShaders();
	void Run();
	

	std::list<IRenderable*> uilist;
	std::list<IRenderable*> geolist;


};
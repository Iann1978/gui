class Engine
{
public:
	Engine();
	~Engine();

	
	void Run();

	std::list<IRenderable*> uilist;
	std::list<IRenderable*> geolist;

};
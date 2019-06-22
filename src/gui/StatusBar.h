#pragma once
#include <Engine/Renderable.h>
#include <Engine/Text.h>
#include <Engine/Image.h>
class StatusBar : public IRenderable
{
	// time
	char timestr[100];
	Text* time;
	void UpdateTime();
	void RenderTime();

	Text* carrier;

	Image* wifi;
	void UpdateWifi();
	Image* volume;

	
public:
	StatusBar();
	~StatusBar();

	void Update();
	void Render();
};


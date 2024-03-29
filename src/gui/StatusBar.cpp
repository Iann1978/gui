#include "prebuild.h"
#include "engine/Time.h"
#include "engine/Input.h"
#include "StatusBar.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <string.h>


StatusBar::StatusBar()
{
	// time
	time = new Text(timestr, 1920/2-150, 5, 24);
	UpdateTime();

	mousepos = new Text(mouseposstr, 1920 - 300, 5, 24);
	UpdateMousePos();

	carrier = new Text("china mobile", 38, 5, 24);

	wifi = new Image("images/wan.dds", 10, 5, 25, 25);
	volume = new Image("images/volume.dds", 1920-40, 5, 25, 25);
}


StatusBar::~StatusBar()
{
	delete volume;
	delete wifi;
	delete carrier;
	delete time;
}


void StatusBar::Update()
{
	UpdateTime();
	UpdateMousePos();
	UpdateWifi();
}

void StatusBar::Render()
{
	RenderTime();
	mousepos->Render();
	carrier->Render();
	wifi->Render();
	volume->Render();
}

void StatusBar::UpdateTime()
{
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(now);

	struct tm buf;
	errno_t err = localtime_s(&buf, &start_time);
	if (std::strftime(timestr, sizeof(timestr), "%F %H:%M:%S", &buf)) {
		int a = 0;
		int b = 0;
	}
}


void StatusBar::UpdateMousePos()
{
	int x = Input::mousePosX;
	int y = Input::mousePosY;
	sprintf_s(mouseposstr, sizeof(mouseposstr), "%d:%d", x, y);
}

void StatusBar::RenderTime()
{
	time->Render();
}

void StatusBar::UpdateWifi()
{
	int n = ((int)Time::time) % 6;
	char path[100];
	sprintf_s(path, "images/wan%d.dds", n);
	wifi->SetTexture(path);
}

#include "prebuild.h"
#include "Engine/Time.h"

#include <chrono>

float Time::deltaTime;

float Time::time;

std::chrono::time_point<std::chrono::system_clock> start;
std::chrono::time_point<std::chrono::system_clock> now;
std::chrono::time_point<std::chrono::system_clock> last;

void Time::UpdateAtGameStart()
{
	start = std::chrono::system_clock::now();
}

void Time::UpdateAtFrameStart()
{
	last = now;
	now = std::chrono::system_clock::now();

	std::chrono::microseconds duation_to_start = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
	std::chrono::microseconds duation_to_last = std::chrono::duration_cast<std::chrono::microseconds>(now - last);
	time = 1.0f * duation_to_start.count() / 1000000;
	deltaTime = 1.0f * duation_to_last.count() / 1000000;
}
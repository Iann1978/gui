#pragma once

class Time
{
public:
	//
	// ժҪ:
	//     The completion time in seconds since the last frame (Read Only).
	static float deltaTime;

	//
	// ժҪ:
	//     The time at the beginning of this frame (Read Only). This is the time in seconds
	//     since the start of the game.
	static float time;

public:
	static void UpdateAtGameStart();
	static void UpdateAtFrameStart();


};


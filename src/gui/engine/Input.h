#pragma once


class Input
{
public:
	
	enum KeyCode
	{
		LeftButton = 0,
		KeyA = 65,
		KeyB,
		KeyC,
		KeyD,
		KeyE,
		KeyF,
		KeyG,
		KeyH,
		KeyI,
		KeyJ,
		KeyK,
		KeyL,
		KeyM,
		KeyN,
		KeyO,
		KeyP,
		KeyQ,
		KeyR,
		KeyS,
		KeyT,
		KeyU,
		KeyV,
		KeyW,
		KeyX,
		KeyY,
		KeyZ,
		KeyCount,
	};
	static double mousePosX;
	static double mousePosY;
	static bool lastFrameButtons[KeyCount];
	static bool buttons[KeyCount];

	static bool GetMouseButtonUp(KeyCode button);
	static bool GetKey(KeyCode key);


	static void UpdateAtFrameStart(void* window);
};


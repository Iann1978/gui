#pragma once

class Camera
{
public:
	static glm::mat4 projectionMatrix;
	static glm::mat4 viewMatrix;
	static void UpdateAtGameStart();
	static void UpdateAtFrameStart();
};


#include "prebuild.h"
#include "Engine/Input.h"


double Input::mousePosX;
double Input::mousePosY;
bool Input::lastFrameButtons[KeyCount];
bool Input::buttons[KeyCount];

bool Input::GetMouseButtonUp(KeyCode button)
{
	return lastFrameButtons[button] && !buttons[button];
}

bool Input::GetKey(KeyCode key)
{
	return buttons[key];
}

void Input::UpdateAtFrameStart(void* window)
{
	memcpy(lastFrameButtons, buttons, sizeof(buttons));

	glfwGetCursorPos((GLFWwindow * )window, &Input::mousePosX, &Input::mousePosY);

	buttons[0] = glfwGetMouseButton((GLFWwindow*)window, 0);

	
	for (int i= GLFW_KEY_A; i<= GLFW_KEY_Z; i++)
	{
		buttons[i] = glfwGetKey((GLFWwindow*)window, i);
	}
}
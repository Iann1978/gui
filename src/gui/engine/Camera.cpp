#include "prebuild.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Screen.h"
#include "Engine/Camera.h"
#include <glm/gtc/quaternion.hpp>

glm::mat4 Camera::projectionMatrix;
glm::mat4 Camera::viewMatrix;

glm::vec3 eye(0,0,0);
glm::vec3 center(0,-3,-2);
glm::vec3 wantup(0,1,0);
glm::vec3 front;
glm::vec3 right;
glm::vec3 up;

void Camera::UpdateAtGameStart()
{
	front = glm::normalize(center - eye);
	right = glm::cross(front, wantup);
	up = glm::cross(right, front);
	center = eye + front;

	projectionMatrix = glm::perspective(glm::radians(75.0f), 1.0f * Screen::width / Screen::height, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::UpdateAtFrameStart()
{
	float deitaTime = Time::deltaTime;

	float moveSpeed = 1.f;	
	float deitaDis = moveSpeed * deitaTime;

	float rotateSpeed = 0.5f;
	float deitaRot = rotateSpeed * deitaTime;



	if (Input::GetKey(Input::KeyA))
	{	
		eye -= deitaDis * right;
	}
	else if (Input::GetKey(Input::KeyD))
	{
		eye += deitaDis * right;
	}
	else if (Input::GetKey(Input::KeyW))
	{
		eye += deitaDis * front;
	}
	else if (Input::GetKey(Input::KeyS))
	{
		eye -= deitaDis * front;
	}
	else if (Input::GetKey(Input::KeyQ))
	{
		glm::quat q = glm::angleAxis(deitaRot, up);
		front = q * front;
		right = glm::cross(front, up);
	}
	else if (Input::GetKey(Input::KeyE))
	{
		glm::quat q = glm::angleAxis(-deitaRot, up);
		front = q * front;
		right = glm::cross(front, up);
		printf("up:%3.2f,%3.2f,%3.2f\n", up.x, up.y, up.z);
	}

	center = eye + front;
	viewMatrix = glm::lookAt(eye, center, up);

}
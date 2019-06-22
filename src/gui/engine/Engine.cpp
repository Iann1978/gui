#include "prebuild.h"
#include <list>

#include <common/shader.hpp>
#include <common/texture.hpp>

#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Camera.h>
#include <Engine/Renderable.h>
#include <Engine/Engine.h>



GLFWwindow* window;
GLuint VertexArrayID;
Engine::Engine()
{
	Screen::width = 1920;
	Screen::height = 1080;

	Time::UpdateAtGameStart();
	Camera::UpdateAtGameStart();

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		//return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(Screen::width, Screen::height, "Tutorial 05 - Textured Cube", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return;
		
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

}
Engine::~Engine()
{

	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Engine::Run()
{
	//std::list<IRenderable*>& renders = uilist;
	do {
		Time::UpdateAtFrameStart();
		Input::UpdateAtFrameStart(window);
		Camera::UpdateAtFrameStart();


		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




		for (std::list<IRenderable*>::iterator it = uilist.begin(); 
			it != uilist.end();
			it++)
		{
			(*it)->Update();
		}


		for (std::list<IRenderable*>::iterator it = uilist.begin(); 
			it != uilist.end();
			it++)
		{
			(*it)->Render();
		}


		for (std::list<IRenderable*>::iterator it = geolist.begin();
			it != geolist.end();
			it++)
		{
			(*it)->Render();
		}


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
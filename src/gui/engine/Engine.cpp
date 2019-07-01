#include "prebuild.h"
#include <list>

#include <common/common_shader.hpp>
#include <common/texture.hpp>

#include <Engine/Time.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>
#include <Engine/Camera.h>
#include <Engine/Shader.h>
#include <Engine/Renderable.h>
#include <Engine/PostProcess.h>
#include <Engine/Engine.h>



GLFWwindow* window;
GLuint VertexArrayID;
Engine::Engine(int width, int height)
{
	Screen::width = width;
	Screen::height = height;
	backgroundColor = glm::vec3(0, 0, 0.07);

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

	LoadAllShaders();

	//postProcess = new PostProcess();
}
Engine::~Engine()
{
	ReleaseAllShaders();

	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

void Engine::LoadAllShaders()
{
	Shader *shader = new Shader("Curve", "shaders/Curve_vert.shader", "shaders/Curve_frag.shader");
	shader = new Shader("Image", "shaders/Image_vert.shader", "shaders/Image_frag.shader");
	shader = new Shader("Text", "shaders/Text_vert.shader", "shaders/Text_frag.shader");
	shader = new Shader("PostProcess_HBlur", "shaders/PostProcess_HBlur_vert.shader", "shaders/PostProcess_HBlur_frag.shader");
	shader = new Shader("PostProcess_VBlur", "shaders/PostProcess_VBlur_vert.shader", "shaders/PostProcess_VBlur_frag.shader");
	shader = new Shader("PostProcess_Add", "shaders/PostProcess_Add_vert.shader", "shaders/PostProcess_Add_frag.shader");
	shader = new Shader("Point_Star", "shaders/Point_Star_vert.shader", "shaders/Point_Star_frag.shader", "shaders/Point_Star_geo.shader");
}

void Engine::ReleaseAllShaders()
{
	delete Shader::Find("Curve");
	delete Shader::Find("Image");
	delete Shader::Find("Text");
	delete Shader::Find("PostProcess_HBlur");
	delete Shader::Find("PostProcess_VBlur");
	delete Shader::Find("PostProcess_Add");
	delete Shader::Find("Point_Star");
}

void Engine::Run()
{
	//std::list<IRenderable*>& renders = uilist;
	do {
		Time::UpdateAtFrameStart();
		Input::UpdateAtFrameStart(window);
		Camera::UpdateAtFrameStart();


		
		glBindFramebuffer(GL_FRAMEBUFFER, postProcess? postProcess->GetCurrentFrameBuffer():0);
		//glBindFramebuffer(GL_FRAMEBUFFER, postProcess->GetCurrentFrameBuffer());
		// Clear the screen
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
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

		if (postProcess)
			postProcess->Render();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
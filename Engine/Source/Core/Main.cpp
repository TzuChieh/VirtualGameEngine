#define GLEW_STATIC

#include "GlfwWindow.h"
#include "GraphicsApi.h"

#include <iostream>

int main(int argc, char** argv)
{
	//std::cout << sizeof(unsigned int) << std::endl;

	xe::GlfwWindow window("Xeno Game Engine ver. 0.0", 1366, 768);
	
	// OpenGL context should be constructed after this call
	if(!window.init())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	while(!window.shouldClose())
	{
		window.update();
		window.refresh();
	}
	
	window.dispose();

	return EXIT_SUCCESS;
}
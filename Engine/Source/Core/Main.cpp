#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static void glfwErrorCallback(int errorCode, const char* errorDescription)
{
	std::cerr << "GLFW Error: " << errorDescription << " <error code = " << errorCode << ">" << std::endl;
}

int main(int argc, char** argv)
{
	glfwSetErrorCallback(glfwErrorCallback);

	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	GLFWwindow* glfwWindow = glfwCreateWindow(1366, 768, "Xeno Game Engine ver. 0.0", NULL, NULL);
	if(!glfwWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(glfwWindow);
	
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
	}

	while(glfwWindowShouldClose(glfwWindow) != GLFW_TRUE)
	{
		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(glfwWindow);
	glfwTerminate();

	return EXIT_SUCCESS;
}
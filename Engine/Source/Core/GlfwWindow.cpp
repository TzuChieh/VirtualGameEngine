#include "GlfwWindow.h"
#include "GraphicsApi.h"

#include <string>
#include <iostream>

using namespace xe;

static void glfwErrorCallback(int errorCode, const char* errorDescription)
{
	std::cerr << "GLFW Error: " << errorDescription << " <error code = " << errorCode << ">" << std::endl;
}

GlfwWindow::GlfwWindow(const std::string& title, const uint32 widthPx, const uint32 heightPx)
: m_title(title), m_widthPx(widthPx), m_heightPx(heightPx), m_glfwWindow(nullptr)
{

}

GlfwWindow::~GlfwWindow()
{

}

bool GlfwWindow::init()
{
	glfwSetErrorCallback(glfwErrorCallback);

	if(!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	m_glfwWindow = glfwCreateWindow(m_widthPx, m_heightPx, m_title.c_str(), NULL, NULL);
	if(!m_glfwWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_glfwWindow);

	return true;
}

void GlfwWindow::update()
{
	glfwPollEvents();
}

void GlfwWindow::refresh()
{
	glfwSwapBuffers(m_glfwWindow);
}

void GlfwWindow::dispose()
{
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

bool GlfwWindow::shouldClose()
{
	return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
}
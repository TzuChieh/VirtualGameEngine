#include "GlfwPlatform.h"
#include "Common/type.h"
#include "Common/ThirdPartyLib/glfw.h"
#include "GlfwInput.h"
#include "GlfwTimer.h"

#include <string>
#include <iostream>

using namespace ve;

static void glfwErrorCallback(int errorCode, const char* errorDescription)
{
	std::cerr << "GLFW Error: " << errorDescription << " <error code = " << errorCode << ">" << std::endl;
}

GlfwPlatform::GlfwPlatform(const std::string& title, const uint32 widthPx, const uint32 heightPx) :
	m_title(title), 
	m_widthPx(widthPx), 
	m_heightPx(heightPx), 
	m_glfwWindow(nullptr), 
	m_input(nullptr),
	m_timer(nullptr)
{

}

GlfwPlatform::~GlfwPlatform()
{

}

bool GlfwPlatform::init(const EngineProxy& engineProxy)
{
	glfwSetErrorCallback(glfwErrorCallback);

	if(!glfwInit())
	{
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	m_glfwWindow = glfwCreateWindow(m_widthPx, m_heightPx, m_title.c_str(), nullptr, nullptr);
	if(!m_glfwWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_glfwWindow);

	m_input = new GlfwInput(m_glfwWindow);
	if(!m_input->init(engineProxy))
	{
		std::cerr << "GlfwInput initialization failed" << std::endl;
		return false;
	}

	m_timer = new GlfwTimer();

	return true;
}

void GlfwPlatform::update()
{
	m_input->update();
}

void GlfwPlatform::refresh()
{
	glfwSwapBuffers(m_glfwWindow);
}

void GlfwPlatform::decompose()
{
	if(m_input)
	{
		m_input->decompose();
		delete m_input;
	}

	delete m_timer;
	
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();
}

bool GlfwPlatform::shouldClose()
{
	return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
}
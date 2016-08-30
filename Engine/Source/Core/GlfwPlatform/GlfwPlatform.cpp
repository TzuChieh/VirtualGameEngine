#include "GlfwPlatform.h"
#include "Common/type.h"
#include "Common/ThirdPartyLib/glfw.h"
#include "GlfwInput.h"
#include "GlfwTimer.h"

#include <string>
#include <iostream>

DEFINE_LOG_SENDER(GlfwPlatform);

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
	if(!init())
	{
		ENGINE_LOG(GlfwPlatform, LogLevel::FATAL_ERROR, "GlfwPlatform init failed");
		return;
	}
}

GlfwPlatform::~GlfwPlatform()
{
	glfwDestroyWindow(m_glfwWindow);
	glfwTerminate();

	ENGINE_LOG(GlfwPlatform, LogLevel::NOTE_MESSAGE, "GlfwPlatform destructed");
}

bool GlfwPlatform::init()
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

	m_input = std::make_unique<GlfwInput>(m_glfwWindow);
	m_timer = std::make_unique<GlfwTimer>();

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

bool GlfwPlatform::shouldClose()
{
	return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
}
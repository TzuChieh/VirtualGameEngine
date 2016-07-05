#include "Engine.h"
#include "GlfwWindow.h"
#include "GraphicsApi.h"

#include <iostream>

using namespace xe;

Engine::Engine()
: m_window(nullptr)
{

}

bool Engine::init()
{
	m_window = new GlfwWindow("Xeno Game Engine ver. 0.0", 1366, 768);

	// OpenGL context should be constructed after this call
	if(!m_window->init())
	{
		std::cerr << "Window initialization failed" << std::endl;
		return false;
	}

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}

	std::cout << "Engine initialized" << std::endl;

	return true;
}

void Engine::start()
{
	std::cout << "Engine started" << std::endl;

	run();
}

void Engine::stop()
{
	std::cout << "Engine stopped" << std::endl;

	dispose();
}

void Engine::run()
{
	while(!m_window->shouldClose())
	{
		update();
		render();
	}

	stop();
}

void Engine::update()
{
	m_window->update();
}

void Engine::render()
{
	// TODO: render stuff

	m_window->refresh();
}

void Engine::dispose()
{
	if(m_window)
	{
		m_window->dispose();
		delete m_window;
	}

	std::cout << "Engine disposed" << std::endl;
}
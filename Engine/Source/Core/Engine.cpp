#include "Common/type.h"
#include "Engine.h"
#include "GlfwPlatform.h"
#include "graphicsApi.h"
#include "Game/GameProgram.h"
#include "Renderer/Renderer.h"
#include "Input.h"

#include <iostream>

using namespace xe;

Engine::Engine()
: m_platform(nullptr), m_gameProgram(nullptr)
{

}

bool Engine::init()
{
	m_platform = new GlfwPlatform("Xeno Game Engine ver. 0.0", 1366, 768);

	// OpenGL context should be constructed after Window initialized
	if(!m_platform->init())
	{
		std::cerr << "Window initialization failed" << std::endl;
		return false;
	}

	// OpenGL core-profile & extension functions should be loaded after GLEW initialized
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{  
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}

	if(!m_gameProgram)
	{
		std::cerr << "GameProgram not specified" << std::endl;
		return false;
	}

	if(!m_gameProgram->init(this))
	{
		std::cerr << "GameProgram initialization failed" << std::endl;
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
	while(!m_platform->shouldClose())
	{
		update();
		render();
	}

	stop();
}

void Engine::update()
{
	m_platform->update();
	m_gameProgram->update();


	// test
	if(m_platform->getInput()->isKeyDown(KeyCode::A))
	{
		std::cout << "A down" << std::endl;
	}
	if(m_platform->getInput()->isKeyUp(KeyCode::A))
	{
		std::cout << "A up" << std::endl;
	}
	if(m_platform->getInput()->isKeyHold(KeyCode::A))
	{
		std::cout << "A hold" << std::endl;
	}
}

void Engine::render()
{
	// TODO: render stuff

	m_platform->refresh();
}

void Engine::dispose()
{
	if(m_platform)
	{
		m_platform->dispose();
		delete m_platform;
	}

	std::cout << "Engine disposed" << std::endl;
}

void Engine::setGameProgram(GameProgram* gameProgram)
{
	m_gameProgram = gameProgram;
}

void Engine::setGameProgram(Renderer* renderer)
{
	m_renderer = renderer;
}
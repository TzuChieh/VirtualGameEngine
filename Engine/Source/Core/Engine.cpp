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
	: m_platform(nullptr), m_gameProgram(nullptr), m_renderer(nullptr)
{

}

Engine::~Engine()
{

}

bool Engine::init()
{
	if(!m_platform)
	{
		std::cerr << "Platform not specified" << std::endl;
		return false;
	}
	// OpenGL context will be constructed after Window initialized
	if(!m_platform->init())
	{
		std::cerr << "Platform initialization failed" << std::endl;
		return false;
	}

	// OpenGL core-profile & extension functions will be loaded after GLEW initialized
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{  
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}

	if(!m_renderer)
	{
		std::cerr << "Renderer not specified" << std::endl;
		return false;
	}
	if(!m_renderer->init())
	{
		std::cerr << "Renderer initialization failed" << std::endl;
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

	decompose();
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
	m_renderer->render();
	m_platform->refresh();
}

void Engine::decompose()
{
	if(m_gameProgram)
	{
		m_gameProgram->decompose();
		delete m_gameProgram;
	}
	if(m_renderer)
	{
		m_renderer->decompose();
		delete m_renderer;
	}
	if(m_platform)
	{
		m_platform->decompose();
		delete m_platform;
	}

	std::cout << "Engine decomposed" << std::endl;
}

void Engine::setPlatform(std::unique_ptr<Platform> platform)
{
	m_platform = platform.release();
}

void Engine::setGameProgram(std::unique_ptr<GameProgram> gameProgram)
{
	m_gameProgram = gameProgram.release();
}

void Engine::setRenderer(std::unique_ptr<Renderer> renderer)
{
	m_renderer = renderer.release();
}

Platform* Engine::getPlatform()
{
	return m_platform;
}

GameProgram* Engine::getGameProgram()
{
	return m_gameProgram;
}

Renderer* Engine::getRenderer()
{
	return m_renderer;
}
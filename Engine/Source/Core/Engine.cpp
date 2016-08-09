#include "Engine.h"
#include "Common/type.h"
#include "graphicsApi.h"
#include "Game/GameProgram.h"
#include "Render/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Input.h"
#include "Platform.h"
#include "Timer.h"

#include <iostream>

using namespace xe;

const LogSender Engine::engineLogSender("Engine");

Engine::Engine() : 
	m_platform(nullptr),
	m_gameProgram(nullptr),
	m_renderer(nullptr),
	m_physicsEngine(nullptr)
{

}

Engine::~Engine()
{

}

bool Engine::init()
{
	if(!verifyEngineSubsystems())
	{
		return false;
	}

	if(!initEngineSubsystems())
	{
		return false;
	}

	ENGINE_LOG(Engine::engineLogSender, LogLevel::NOTE_MESSAGE, "initialized");

	return true;
}

void Engine::start()
{
	ENGINE_LOG(Engine::engineLogSender, LogLevel::NOTE_MESSAGE, "started");

	run();
}

void Engine::stop()
{
	ENGINE_LOG(Engine::engineLogSender, LogLevel::NOTE_MESSAGE, "stopped");

	decompose();
}

void Engine::run()
{
	float64 lastTimeS        = m_platform->getTimer()->getCurrentTimeS();
	float64 currentTimeS     = lastTimeS;
	float64 unprocessedTimeS = 0.0;

	// TEMP
	const float64 targetUpdateStepS = 1.0f / 60.0f;

	while(!m_platform->shouldClose())
	{
		lastTimeS        = currentTimeS;
		currentTimeS     = m_platform->getTimer()->getCurrentTimeS();
		unprocessedTimeS += (currentTimeS - lastTimeS);

		while(unprocessedTimeS > targetUpdateStepS)
		{
			update(targetUpdateStepS);

			unprocessedTimeS -= targetUpdateStepS;
		}

		render();
	}

	stop();
}

void Engine::update(float deltaS)
{
	m_platform->update();
	m_physicsEngine->update(deltaS);
	m_gameProgram->update(deltaS);
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
	}
	if(m_physicsEngine)
	{
		m_physicsEngine->decompose();
	}
	if(m_renderer)
	{
		m_renderer->decompose();
	}
	if(m_platform)
	{
		m_platform->decompose();
	}

	ENGINE_LOG(Engine::engineLogSender, LogLevel::NOTE_MESSAGE, "decomposed");
}

Platform*      Engine::getPlatform()      { return m_platform.get();      }
GameProgram*   Engine::getGameProgram()   { return m_gameProgram.get();   }
Renderer*      Engine::getRenderer()      { return m_renderer.get();      }
PhysicsEngine* Engine::getPhysicsEngine() { return m_physicsEngine.get(); }

void Engine::setPlatform(std::unique_ptr<Platform> platform)
{
	m_platform = std::move(platform);
}

void Engine::setGameProgram(std::unique_ptr<GameProgram> gameProgram)
{
	m_gameProgram = std::move(gameProgram);
}

void Engine::setRenderer(std::unique_ptr<Renderer> renderer)
{
	m_renderer = std::move(renderer);
}

void Engine::setPhysicsEngine(std::unique_ptr<PhysicsEngine> physicsEngine)
{
	m_physicsEngine = std::move(physicsEngine);
}

bool Engine::verifyEngineSubsystems()
{
	if(!m_platform || !m_renderer || !m_physicsEngine || !m_gameProgram)
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "subsystem validation failed");
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR,
		           "The following subsystems are required : Platform, Renderer, PhysicsEngine and GameProgram.");
		decompose();
		return false;
	}

	return true;
}

bool Engine::initEngineSubsystems()
{
	// OpenGL context will be constructed after Window initialized
	if(!m_platform->init())
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "Platform initialization failed");
		decompose();
		return false;
	}

	// OpenGL core-profile & extension functions will be loaded after GLEW initialized
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "GLEW initialization failed");
		decompose();
		return false;
	}

	if(!m_renderer->init())
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "Renderer initialization failed");
		decompose();
		return false;
	}

	if(!m_physicsEngine->init())
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "PhysicsEngine initialization failed");
		decompose();
		return false;
	}

	if(!m_gameProgram->init(this))
	{
		ENGINE_LOG(Engine::engineLogSender, LogLevel::FATAL_ERROR, "GameProgram initialization failed");
		decompose();
		return false;
	}

	return true;
}
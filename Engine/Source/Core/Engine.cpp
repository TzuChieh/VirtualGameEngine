#include "Engine.h"
#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Game/GameProgram.h"
#include "Render/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Input.h"
#include "Platform.h"
#include "Timer.h"
#include "Core/EngineProxy.h"

#include <iostream>

DEFINE_LOG_SENDER(Engine);

using namespace ve;

Engine::Engine(Platform* platform) :
	m_platform(platform),
	m_gameProgram(nullptr),
	m_renderer(nullptr),
	m_physicsEngine(nullptr), 
	m_world(this)
{
	// OpenGL core-profile & extension functions will be loaded after GLEW initialized
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "GLEW initialization failed");
		decompose();
	}

	if(!m_world.init())
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "World initialization failed");
		decompose();
	}
}

Engine::~Engine()
{

}

bool Engine::initSubsystems()
{
	if(!verifyEngineSubsystems())
	{
		return false;
	}

	if(!initEngineSubsystems())
	{
		return false;
	}

	ENGINE_LOG(Engine, LogLevel::NOTE_MESSAGE, "initialized");

	return true;
}

void Engine::start()
{
	ENGINE_LOG(Engine, LogLevel::NOTE_MESSAGE, "started");

	run();
}

void Engine::stop()
{
	ENGINE_LOG(Engine, LogLevel::NOTE_MESSAGE, "stopped");

	decompose();
}

void Engine::run()
{
	float64 lastTimeS          = m_platform->getTimer()->getCurrentTimeS();
	float64 currentTimeS       = lastTimeS;
	float64 unprocessedTimeS   = 0.0;
	float64 fpsTimeAccumulator = 0.0;

	uint32 fps = 0;
	uint32 fpsCounter = 0;

	// TEMP
	const float64 targetUpdateStepS = 1.0f / 60.0f;

	while(!m_platform->shouldClose())
	{
		bool needRendering = false;

		lastTimeS        = currentTimeS;
		currentTimeS     = m_platform->getTimer()->getCurrentTimeS();
		unprocessedTimeS += (currentTimeS - lastTimeS);

		while(unprocessedTimeS > targetUpdateStepS)
		{
			update(static_cast<float32>(targetUpdateStepS));

			unprocessedTimeS   -= targetUpdateStepS;
			fpsTimeAccumulator += targetUpdateStepS;

			needRendering = true;
		}

		if(needRendering)
		{
			render();

			fpsCounter++;

			if(fpsTimeAccumulator >= 1.0)
			{
				fps = fpsCounter;

				fpsTimeAccumulator -= 1.0;
				fpsCounter = 0;

				//std::cout << "FPS: " << fps << std::endl;
			}

			needRendering = false;
		}
		

		// debug: naive loop
		/*update(targetUpdateStepS);
		render();*/
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

	ENGINE_LOG(Engine, LogLevel::NOTE_MESSAGE, "decomposed");
}

Platform*      Engine::getPlatform()      { return m_platform;      }
GameProgram*   Engine::getGameProgram()   { return m_gameProgram.get();   }
Renderer*      Engine::getRenderer()      { return m_renderer.get();      }
PhysicsEngine* Engine::getPhysicsEngine() { return m_physicsEngine.get(); }

World* Engine::getWorld() { return &m_world; }

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
	if(!m_renderer || !m_physicsEngine || !m_gameProgram)
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "subsystem validation failed");
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR,
		           "The following subsystems are required : Renderer, PhysicsEngine and GameProgram.");
		decompose();
		return false;
	}

	return true;
}

bool Engine::initEngineSubsystems()
{
	if(!m_renderer->init(EngineProxy(this)))
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "Renderer initialization failed");
		decompose();
		return false;
	}

	if(!m_physicsEngine->init(this))
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "PhysicsEngine initialization failed");
		decompose();
		return false;
	}

	if(!m_gameProgram->init(this))
	{
		ENGINE_LOG(Engine, LogLevel::FATAL_ERROR, "GameProgram initialization failed");
		decompose();
		return false;
	}

	return true;
}
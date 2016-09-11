#pragma once

#include "Common/Type.h"
#include "Common/logging.h"
#include "Resource/World/World.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(Engine);

namespace ve
{

class Platform;
class GameProgram;
class Renderer;
class PhysicsEngine;

class Engine
{
public:
	Engine(Platform* platform);
	~Engine();

	bool initSubsystems();
	void start();

	void setGameProgram(std::unique_ptr<GameProgram> gameProgram);
	void setRenderer(std::unique_ptr<Renderer> renderer);
	void setPhysicsEngine(std::unique_ptr<PhysicsEngine> physicsEngine);

	Platform*      getPlatform();
	GameProgram*   getGameProgram();
	Renderer*      getRenderer();
	PhysicsEngine* getPhysicsEngine();

	// TODO: should return WorldProxy instead, thus making engine to decide when to flush
	World* getWorld();

private:
	void run();
	void update(float deltaS);
	void render();
	void stop();
	void decompose();

	bool verifyEngineSubsystems();
	bool initEngineSubsystems();

	Platform* m_platform;

	// subsystems
	std::unique_ptr<GameProgram>   m_gameProgram;
	std::unique_ptr<Renderer>      m_renderer;
	std::unique_ptr<PhysicsEngine> m_physicsEngine;

	// database
	World m_world;

private:
	static const LogSender engineLogSender;
};

}
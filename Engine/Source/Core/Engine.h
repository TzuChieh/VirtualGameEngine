#pragma once

#include "Common/Type.h"

#include <memory>

namespace xe
{

class Platform;
class GameProgram;
class Renderer;
class PhysicsEngine;

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void start();

	void setPlatform(std::unique_ptr<Platform> platform);
	void setGameProgram(std::unique_ptr<GameProgram> gameProgram);
	void setRenderer(std::unique_ptr<Renderer> renderer);
	void setPhysicsEngine(std::unique_ptr<PhysicsEngine> physicsEngine);

	Platform*      getPlatform();
	GameProgram*   getGameProgram();
	Renderer*      getRenderer();
	PhysicsEngine* getPhysicsEngine();

private:
	void run();
	void update(float deltaS);
	void render();
	void stop();
	void decompose();

	bool verifyEngineSubsystems();
	bool initEngineSubsystems();

	// subsystems
	std::unique_ptr<Platform>      m_platform;
	std::unique_ptr<GameProgram>   m_gameProgram;
	std::unique_ptr<Renderer>      m_renderer;
	std::unique_ptr<PhysicsEngine> m_physicsEngine;
};

}
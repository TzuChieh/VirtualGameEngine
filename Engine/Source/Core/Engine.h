#pragma once

#include "Common/Type.h"

#include <memory>

namespace xe
{

class Platform;
class GameProgram;
class Renderer;

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

private:
	void run();
	void update();
	void render();
	void stop();
	void decompose();

	Platform* m_platform;
	GameProgram* m_gameProgram;
	Renderer* m_renderer;
};

}
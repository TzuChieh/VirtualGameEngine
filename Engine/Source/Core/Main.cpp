#include "Engine.h"
#include "Game/TestGameProgram/TestGameProgram.h"
#include "Core/GlfwPlatform.h"
#include "Render/TestRenderer/TestRenderer.h"
#include "Physics/TestPhysicsEngine/TestPhysicsEngine.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<xe::Platform> platform = std::make_unique<xe::GlfwPlatform>("Xeno Game Engine ver. 0.0", 1366, 768);
	std::unique_ptr<xe::Renderer> renderer = std::make_unique<xe::TestRenderer>();
	std::unique_ptr<xe::PhysicsEngine> physicsEngine = std::make_unique<xe::TestPhysicsEngine>();
	std::unique_ptr<xe::GameProgram> gameProgram = std::make_unique<xe::TestGameProgram>();

	xe::Engine engine;
	engine.setPlatform(std::move(platform));
	engine.setRenderer(std::move(renderer));
	engine.setPhysicsEngine(std::move(physicsEngine));
	engine.setGameProgram(std::move(gameProgram));

	if(!engine.init())
	{
		std::cerr << "Engine initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	engine.start();

	return EXIT_SUCCESS;
}
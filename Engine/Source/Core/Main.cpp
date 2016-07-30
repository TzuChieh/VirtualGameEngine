#include "Engine.h"
#include "Game/TestGameProgram/TestGameProgram.h"
#include "Core/GlfwPlatform.h"
#include "Renderer/TestRenderer/TestRenderer.h"

#include <iostream>
#include <memory>

int main(int argc, char** argv)
{
	std::unique_ptr<xe::Platform> platform(new xe::GlfwPlatform("Xeno Game Engine ver. 0.0", 1366, 768));
	std::unique_ptr<xe::Renderer> renderer(new xe::TestRenderer);
	std::unique_ptr<xe::GameProgram> gameProgram(new xe::TestGameProgram);

	xe::Engine engine;
	engine.setPlatform(std::move(platform));
	engine.setRenderer(std::move(renderer));
	engine.setGameProgram(std::move(gameProgram));

	if(!engine.init())
	{
		std::cerr << "Engine initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	engine.start();

	return EXIT_SUCCESS;
}
#include "Engine.h"
#include "Game/TestGameProgram/TestGameProgram.h"
#include "Core/GlfwPlatform/GlfwPlatform.h"
#include "Render/TestRenderer/TestRenderer.h"
#include "Physics/TestPhysicsEngine/TestPhysicsEngine.h"

#include <iostream>
#include <memory>

class TestClass
{
private:
	std::unordered_map<int, std::unique_ptr<float>> m_map;
};

void test();

int main(int argc, char** argv)
{
	test();

	// OpenGL context will be constructed after Platform created
	ve::GlfwPlatform platform("Virtual Game Engine ver. 0.0", 1366, 768);

	ve::Engine engine(&platform);
	
	// subsystems can only be created after engine constructed
	std::unique_ptr<ve::Renderer> renderer = std::make_unique<ve::TestRenderer>();
	std::unique_ptr<ve::PhysicsEngine> physicsEngine = std::make_unique<ve::TestPhysicsEngine>();
	std::unique_ptr<ve::GameProgram> gameProgram = std::make_unique<ve::TestGameProgram>();

	engine.setRenderer(std::move(renderer));
	engine.setPhysicsEngine(std::move(physicsEngine));
	engine.setGameProgram(std::move(gameProgram));

	if(!engine.initSubsystems())
	{
		std::cerr << "Engine initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	engine.start();

	return EXIT_SUCCESS;
}

void test()
{
	std::vector<TestClass> testVector;


}
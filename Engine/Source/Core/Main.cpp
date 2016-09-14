#include "Engine.h"
#include "Game/TestGameProgram/TestGameProgram.h"
#include "Core/GlfwPlatform/GlfwPlatform.h"
#include "Render/TestRenderer/TestRenderer.h"
#include "Physics/TestPhysicsEngine/TestPhysicsEngine.h"
#include "Utility/TStableIndexDenseArray.h"

#include <random>
#include <iostream>
#include <memory>
#include <vector>

void test();

int main(int argc, char** argv)
{
	//test();

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
	using namespace ve;
	TStableIndexDenseArray<float> arr(100);


	const auto& index1 = arr.add(10.0f);
	arr.remove(index1);

	std::vector<std::size_t> indices;
	
	/*for(uint32 i = 0; i < 1000; i++)
	{
		const auto& id = arr.add(rand());
		indices.push_back(id);
	}

	for(uint32 i = 0; i < 1000; i++)
	{
		if(rand() > 10000)
		{
			arr.remove(indices[i]);
		}
	}

	for(uint32 i = 0; i < 1000; i++)
	{
		const auto& id = arr.add(rand());
		indices.push_back(id);
	}*/

	/*for(auto& value : arr)
	{

	}*/

	const auto& id1 = arr.add(10.0f);
	const auto& id2 = arr.add(20.0f);
	const auto& id3 = arr.add(33.0f);
	const auto& id4 = arr.add(20.0f);

	arr.remove(id1);
	arr.remove(id2);
	arr.remove(id2);// invalid stable index detected

	const auto& id5 = arr.add(5.0f);
	const auto& id6 = arr.add(77.0f);

	arr.remove(id4);

	const auto& id7 = arr.add(4.0f);

	std::cout << "get: " << arr[id1] << std::endl;// 77
	std::cout << "get: " << arr[id2] << std::endl;// 5
	std::cout << "get: " << arr[id4] << std::endl;// 4

	// 77 33 5 4
	for(const auto& value : arr)
	{
		std::cout << "value: " << value << std::endl;
	}

	exit(EXIT_SUCCESS);
}
#include "CameraControl.h"
#include "Core/Engine.h"
#include "Core/Platform.h"
#include "Core/Input.h"

#include <iostream>

using namespace xe;

CameraControl::~CameraControl()
{

}

void CameraControl::execute(float32 deltaS, Engine* engine)
{
	const Input* input = engine->getPlatform()->getInput();

	if(input->isKeyDown(KeyCode::A))
	{
		std::cout << "A down" << std::endl;
	}
	if(input->isKeyUp(KeyCode::A))
	{
		std::cout << "A up" << std::endl;
	}
	if(input->isKeyHold(KeyCode::A))
	{
		std::cout << "A hold" << std::endl;
	}
}
#include "CameraControl.h"
#include "Core/Engine.h"
#include "Core/Platform.h"
#include "Core/Input.h"
#include "Core/Timer.h"
#include "Physics/Component/CTransform.h"
#include "Math/Vector3f.h"
#include "Core/EngineProxy.h"

#include <iostream>

using namespace xe;

CameraControl::~CameraControl()
{

}

void CameraControl::execute(float32 deltaS, Scene* scene, const EngineProxy& engineProxy)
{
	CTransform* transform = getParentEntity().getComponent<CTransform>();
	const Input* input = engineProxy.getInput();

	/*float64 cursorX;
	float64 cursorY;

	input->getCursorPositionPx(&cursorX, &cursorY);
	std::cout << "cursor abs. x: " << cursorX << std::endl;
	std::cout << "cursor abs. y: " << cursorY << std::endl;

	input->getCursorMovementDeltaPx(&cursorX, &cursorY);
	std::cout << "cursor delta x: " << cursorX << std::endl;
	std::cout << "cursor delta y: " << cursorY << std::endl;*/

	//std::cout << "timer test: " << deltaS << std::endl;

	MouseButtonCode testCode = MouseButtonCode::RIGHT;
	if(input->isMouseButtonDown(testCode))
	{
		std::cout << "mouse button down" << std::endl;
	}
	if(input->isMouseButtonHold(testCode))
	{
		std::cout << "mouse button hold" << std::endl;
	}
	if(input->isMouseButtonUp(testCode))
	{
		std::cout << "mouse button up" << std::endl;
	}

	if(transform)
	{
		Vector3f moveDir(0, 0, 0);
		float32 moveSpeed = 5.0f;
		bool hasMoved = false;

		if(input->isKeyHold(KeyCode::A))
		{
			moveDir.x -= 1.0f;
			hasMoved = true;
		}
		if(input->isKeyHold(KeyCode::D))
		{
			moveDir.x += 1.0f;
			hasMoved = true;
		}
		if(input->isKeyHold(KeyCode::W))
		{
			moveDir.z -= 1.0f;
			hasMoved = true;
		}
		if(input->isKeyHold(KeyCode::S))
		{
			moveDir.z += 1.0f;
			hasMoved = true;
		}

		if(hasMoved && moveDir.squaredLength() > 0.001f)
		{
			moveDir.normalizeLocal();
			moveDir.mulLocal(moveSpeed * deltaS);
			transform->setPosition(moveDir.addLocal(transform->getPosition()));
		}
	}
}
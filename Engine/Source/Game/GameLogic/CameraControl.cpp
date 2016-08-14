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

	static bool bVirtualizeCursor = false;

	if(input->isKeyUp(KeyCode::T))
	{
		bVirtualizeCursor = !bVirtualizeCursor;

		if(bVirtualizeCursor)
		{
			input->virtualizeCursor();
		}
		else
		{
			input->unvirtualizeCursor();
		}
	}

	if(transform)
	{
		processCameraTranslation(input, transform, deltaS);

		if(input->isMouseButtonHold(MouseButtonCode::LEFT))
		{
			processCameraRotation(input, transform, deltaS);
		}
	}
}

void CameraControl::processCameraTranslation(const Input* input, CTransform* transform, const float32 deltaS) const
{
	Vector3f moveDir(0, 0, 0);
	float32 moveSpeed = 5.0f;
	bool hasMoved = false;

	if(input->isKeyHold(KeyCode::A))
	{
		moveDir.subLocal(transform->getRightUnitDirection());
		hasMoved = true;
	}
	if(input->isKeyHold(KeyCode::D))
	{
		moveDir.addLocal(transform->getRightUnitDirection());
		hasMoved = true;
	}
	if(input->isKeyHold(KeyCode::W))
	{
		moveDir.addLocal(transform->getForwardUnitDirection());
		hasMoved = true;
	}
	if(input->isKeyHold(KeyCode::S))
	{
		moveDir.subLocal(transform->getForwardUnitDirection());
		hasMoved = true;
	}

	if(hasMoved && moveDir.squaredLength() > 0.001f)
	{
		moveDir.normalizeLocal();
		moveDir.mulLocal(moveSpeed * deltaS);
		transform->setPosition(moveDir.addLocal(transform->getPosition()));
	}
}

void CameraControl::processCameraRotation(const Input* input, CTransform* transform, const float32 deltaS) const
{
	float64 cursorDeltaXpx;
	float64 cursorDeltaYpx;
	input->getCursorMovementDeltaPx(&cursorDeltaXpx, &cursorDeltaYpx);

	bool rotY = cursorDeltaXpx != 0;
	bool rotX = cursorDeltaYpx != 0;

	const float32 sensitivity = 0.2f;

	if(rotY)
	{
		transform->rotateDeg(Vector3f::UNIT_Y_AXIS, static_cast<float32>(-cursorDeltaXpx) * sensitivity);
	}

	if(rotX)
	{
		transform->rotateDeg(transform->getRightUnitDirection(), static_cast<float32>(cursorDeltaYpx) * sensitivity);
	}
}
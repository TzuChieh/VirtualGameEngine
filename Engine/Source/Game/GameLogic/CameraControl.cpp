#include "CameraControl.h"
#include "Core/Engine.h"
#include "Core/Platform.h"
#include "Core/Input.h"
#include "Core/Timer.h"
#include "Physics/Component/CTransform.h"
#include "Math/Vector3f.h"

#include <iostream>

using namespace xe;

CameraControl::~CameraControl()
{

}

void CameraControl::execute(float32 deltaS, Engine* engine)
{
	CTransform* transform = getParentEntity().getComponent<CTransform>();
	const Input* input = engine->getPlatform()->getInput();

	std::cout << "timer test: " << engine->getPlatform()->getTimer()->getCurrentTimeMs() << std::endl;

	if(transform)
	{
		Vector3f moveStep(0, 0, 0);
		float32 moveSpeed = 10.0f;

		if(input->isKeyHold(KeyCode::A))
		{
			moveStep.x -= 1.0f;
		}
		if(input->isKeyHold(KeyCode::D))
		{
			moveStep.x += 1.0f;
		}
		if(input->isKeyHold(KeyCode::W))
		{
			moveStep.z -= 1.0f;
		}
		if(input->isKeyHold(KeyCode::S))
		{
			moveStep.z += 1.0f;
		}

		moveStep.mulLocal(moveSpeed * deltaS);
		transform->setPosition(moveStep.addLocal(transform->getPosition()));
	}
}
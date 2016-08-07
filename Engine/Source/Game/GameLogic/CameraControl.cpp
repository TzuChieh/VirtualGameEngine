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

void CameraControl::execute(float32 deltaS, const EngineProxy& engineProxy)
{
	CTransform* transform = getParentEntity().getComponent<CTransform>();
	const Input* input = engineProxy.getInput();

	std::cout << "timer test: " << deltaS << std::endl;

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
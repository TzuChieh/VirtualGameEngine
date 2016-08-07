#pragma once

#include "Game/GameProgram.h"
#include "Resource/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/Component/TIndexedComponentManager.h"

#include <vector>

namespace xe
{

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

private:
	virtual bool initScene(Scene* scene, const EngineProxy& engineProxy) override;
};

}
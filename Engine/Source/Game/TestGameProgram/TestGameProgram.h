#pragma once

#include "Game/GameProgram.h"
#include "Resource/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/Component/TIndexedComponentManager.h"

#include <vector>

namespace ve
{

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

private:
	virtual bool initScene(World* world, const EngineProxy& engineProxy) override;
};

}
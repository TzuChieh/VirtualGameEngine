#pragma once

#include "Game/GameProgram.h"
#include "Resource/World/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"

#include <vector>

namespace ve
{

class TestGameProgram final : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

private:
	virtual bool initWorld(World* world, const EngineProxy& engineProxy) override;
};

}
#pragma once

#include "Common/type.h"
#include "Resource/World/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"
#include "TestComponentProcessor.h"

#include <memory>

namespace ve
{

class Engine;
class EngineProxy;

class GameProgram
{
	friend class Engine;

public:
	GameProgram();
	virtual ~GameProgram() = 0;

	//std::shared_ptr<ComponentHandle> addTestComponent(const CTestComponent& testComponent);
	//std::shared_ptr<ComponentHandle> addGameLogicGroup(const CGameLogicGroup& gameLogicGroup);

private:
	Engine* m_engine;
	TestComponentProcessor m_testComponentProcessor;

	bool init(Engine* engine);
	void update(float32 deltaS);
	void decompose();

	virtual bool initWorld(World* world, const EngineProxy& engineProxy) = 0;
};

}
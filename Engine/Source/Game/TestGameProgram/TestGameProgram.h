#pragma once

#include "Game/GameProgram.h"
#include "Resource/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/Component/TIndexedComponentManager.h"

#include <vector>

namespace xe
{

class Component;
class Engine;

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

	virtual std::shared_ptr<ComponentHandle> addTestComponent(const CTestComponent& testComponent) override;
	virtual std::shared_ptr<ComponentHandle> addGameLogicGroup(const CGameLogicGroup& gameLogicGroup) override;

	virtual inline Scene* getScene() override
	{
		return m_scene;
	}

private:
	Engine* m_engine;
	Scene* m_scene;

	TIndexedComponentManager<CTestComponent> m_testComponents;
	TIndexedComponentManager<CGameLogicGroup> m_gameLogicGroups;

	virtual bool init(Engine* engine) override;
	virtual void update(float32 deltaS) override;
	virtual void decompose() override;

	void initScene(Engine* engine);
};

}
#pragma once

#include "Common/type.h"
#include "Resource/Component/ComponentHandle.h"
#include "Resource/Component/TIndexedComponentManager.h"

#include "Resource/Component/CTestComponent.h"
#include "Game/Component/CGameLogicGroup.h"

#include <memory>

namespace xe
{

class Scene;
class Engine;
class EngineProxy;

class GameProgram
{
	friend class Engine;

public:
	GameProgram();
	virtual ~GameProgram() = 0;

	std::shared_ptr<ComponentHandle> addTestComponent(const CTestComponent& testComponent);
	std::shared_ptr<ComponentHandle> addGameLogicGroup(const CGameLogicGroup& gameLogicGroup);

private:
	Engine* m_engine;
	std::unique_ptr<Scene> m_scene;

	TIndexedComponentManager<CTestComponent> m_testComponents;
	TIndexedComponentManager<CGameLogicGroup> m_gameLogicGroups;

	bool init(Engine* engine);
	void update(float32 deltaS);
	void decompose();

	virtual bool initScene(Scene* scene, const EngineProxy& engineProxy) = 0;
};

}
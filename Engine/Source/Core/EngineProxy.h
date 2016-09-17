#pragma once

#include "Common/type.h"

#include <memory>

namespace ve
{

class Engine;
class Input;
class World;

//class ComponentHandle;
//
//class CTestComponent;
//class CGameLogicGroup;
//
//class CCamera;
//class CStaticMeshGroup;
//
//class CTransform;

class EngineProxy
{
public:
	EngineProxy();
	explicit EngineProxy(Engine* engine);

	uint32 getDisplayWidthPx() const;
	uint32 getDisplayHeightPx() const;

	const Input* getInput() const;

	// TODO: should return WorldProxy instead, thus making engine to decide when to flush
	World* getWorld();

	/*std::shared_ptr<ComponentHandle> addToEngine(const CTestComponent& testComponent);
	std::shared_ptr<ComponentHandle> addToEngine(const CGameLogicGroup& gameLogicGroup);

	std::shared_ptr<ComponentHandle> addToEngine(const CCamera& camera);
	std::shared_ptr<ComponentHandle> addToEngine(const CStaticMeshGroup& staticMeshGroup);

	std::shared_ptr<ComponentHandle> addToEngine(const CTransform& transform);*/

private:
	Engine* m_engine;
};

}
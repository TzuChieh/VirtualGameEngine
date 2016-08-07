#pragma once

#include "Common/type.h"

#include <memory>

namespace xe
{

class Engine;
class ComponentHandle;

class CTestComponent;
class CGameLogicGroup;

class CCamera;
class CStaticMeshGroup;

class CTransform;

class EngineProxy
{
public:
	explicit EngineProxy(Engine* engine);

	uint32 getDisplayWidthPx() const;
	uint32 getDisplayHeightPx() const;

	std::shared_ptr<ComponentHandle> addToEngine(const CTestComponent& testComponent);
	std::shared_ptr<ComponentHandle> addToEngine(const CGameLogicGroup& gameLogicGroup);

	std::shared_ptr<ComponentHandle> addToEngine(const CCamera& camera);
	std::shared_ptr<ComponentHandle> addToEngine(const CStaticMeshGroup& staticMeshGroup);

	std::shared_ptr<ComponentHandle> addToEngine(const CTransform& transform);

private:
	Engine* m_engine;
};

}
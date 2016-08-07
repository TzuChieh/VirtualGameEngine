#include "EngineProxy.h"
#include "Engine.h"
#include "Platform.h"
#include "Game/GameProgram.h"
#include "Render/Renderer.h"
#include "Physics/PhysicsEngine.h"

#include <iostream>

using namespace xe;

EngineProxy::EngineProxy(Engine* engine) :
	m_engine(engine)
{
	if(!m_engine)
	{
		std::cerr << "EngineProxy Warning: null engine pointer" << std::endl;
	}
}

uint32 EngineProxy::getDisplayWidthPx() const
{
	return m_engine->getPlatform()->getWidthPx();
}

uint32 EngineProxy::getDisplayHeightPx() const
{
	return m_engine->getPlatform()->getHeightPx();
}

std::shared_ptr<ComponentHandle> EngineProxy::addToEngine(const CTestComponent& testComponent)
{
	return m_engine->getGameProgram()->addTestComponent(testComponent);
}

std::shared_ptr<ComponentHandle> EngineProxy::addToEngine(const CGameLogicGroup& gameLogicGroup)
{
	return m_engine->getGameProgram()->addGameLogicGroup(gameLogicGroup);
}

std::shared_ptr<ComponentHandle> EngineProxy::addToEngine(const CCamera& camera)
{
	return m_engine->getRenderer()->addCamera(camera);
}

std::shared_ptr<ComponentHandle> EngineProxy::addToEngine(const CStaticMeshGroup& staticMeshGroup)
{
	return m_engine->getRenderer()->addStaticMeshGroup(staticMeshGroup);
}

std::shared_ptr<ComponentHandle> EngineProxy::addToEngine(const CTransform& transform)
{
	return m_engine->getPhysicsEngine()->addTransform(transform);
}
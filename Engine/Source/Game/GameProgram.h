#pragma once

#include "Common/type.h"
#include "Resource/Component/ComponentHandle.h"

#include <memory>

namespace xe
{

class Component;
class CTestComponent;
class CGameLogicGroup;
class Scene;

class GameProgram
{
	friend class Engine;

public:
	virtual ~GameProgram() = 0;

	virtual Scene* getScene() = 0;
	virtual std::shared_ptr<ComponentHandle> addTestComponent(const CTestComponent& testComponent) = 0;
	virtual std::shared_ptr<ComponentHandle> addGameLogicGroup(const CGameLogicGroup& gameLogicGroup) = 0;

private:
	virtual void update(float32 deltaS) = 0;
	virtual bool init(Engine* engine) = 0;
	virtual void decompose() = 0;
};

}
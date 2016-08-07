#pragma once

#include "Common/type.h"
#include "Resource/Entity/Entity.h"

namespace xe
{

class Engine;
class EngineProxy;
class Scene;

class GameLogic
{
	friend class CGameLogicGroup;

public:
	virtual ~GameLogic() = 0;

	virtual void execute(float32 deltaS, Scene* scene, const EngineProxy& engineProxy) = 0;

protected:
	Entity getParentEntity() const;

private:
	Entity m_parentEntity;

	void setParentEntity(const Entity& entity);
};

}
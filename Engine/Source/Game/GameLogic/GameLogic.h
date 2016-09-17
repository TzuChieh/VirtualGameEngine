#pragma once

#include "Common/type.h"
#include "Resource/World/Entity/Entity.h"

namespace ve
{

class Engine;
class EngineProxy;
class World;

class GameLogic
{
	friend class CGameLogicGroup;

public:
	GameLogic();
	virtual ~GameLogic() = 0;

	virtual void execute(float32 deltaS, World* world, const EngineProxy& engineProxy) = 0;

protected:
	Entity getParentEntity() const;

private:
	Entity m_parentEntity;

	void setParentEntity(const Entity& entity);
};

}
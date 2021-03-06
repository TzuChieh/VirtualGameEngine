#pragma once

#include "Common/type.h"
#include "Resource/World/Component/Component.h"
#include "Game/GameLogic/GameLogic.h"

#include <unordered_map>
#include <memory>
#include <string>

namespace ve
{

class Engine;
class GameLogic;
class EngineProxy;
class World;

class CGameLogicGroup : public Component
{
public:
	CGameLogicGroup() = default;
	virtual ~CGameLogicGroup() override;

	virtual ComponentTypeId getTypeId() override;

	void initGameLogics();
	void executeGameLogics(float32 deltaS, World* world, const EngineProxy& engineProxy);

	void addGameLogic(const std::string& logicName, std::shared_ptr<GameLogic> gameLogic);

private:
	std::unordered_map<std::string, std::shared_ptr<GameLogic>> m_gameLogicsNameMap;
};

}
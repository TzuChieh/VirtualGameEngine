#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
#include "Game/GameLogic/GameLogic.h"

#include <unordered_map>
#include <memory>
#include <string>

namespace xe
{

class Engine;
class GameLogic;

class CGameLogicGroup : public Component
{
public:
	CGameLogicGroup();
	virtual ~CGameLogicGroup() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	void executeAll(float32 deltaS, Engine* engine);

	void addGameLogic(const std::string& logicName, std::shared_ptr<GameLogic> gameLogic);

private:
	std::unordered_map<std::string, std::shared_ptr<GameLogic>> m_gameLogicsNameMap;
};

}
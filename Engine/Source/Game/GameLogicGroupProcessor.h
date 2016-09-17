#pragma once

#include "Resource/World/Event/TComponentListener.h"

namespace ve
{

class CGameLogicGroup;

class GameLogicGroupProcessor : public TComponentListener<CGameLogicGroup>
{
public:
	virtual ~GameLogicGroupProcessor() override;

	virtual void onComponentAdded(CGameLogicGroup* component, const ComponentIndexType index) override;
	virtual void onComponentRemoval(CGameLogicGroup* component, const ComponentIndexType index) override;
};

}
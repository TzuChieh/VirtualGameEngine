#pragma once

#include "Resource/World/Component/TComponentManagerActionListener.h"

namespace ve
{

class CGameLogicGroup;

class GameLogicGroupActionListener : public TComponentManagerActionListener<CGameLogicGroup>
{
public:
	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CGameLogicGroup>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CGameLogicGroup>>& targetComponent) override;
};

}
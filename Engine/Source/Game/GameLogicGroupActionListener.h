#pragma once

#include "Resource/Component/TComponentManagerActionListener.h"

namespace xe
{

class CGameLogicGroup;

class GameLogicGroupActionListener : public TComponentManagerActionListener<CGameLogicGroup>
{
public:
	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CGameLogicGroup>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CGameLogicGroup>>& targetComponent) override;
};

}
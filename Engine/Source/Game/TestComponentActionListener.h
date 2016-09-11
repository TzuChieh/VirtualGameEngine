#pragma once

#include "Resource/World/Component/TComponentManagerActionListener.h"

namespace ve
{

class CTestComponent;

class TestComponentActionListener : public TComponentManagerActionListener<CTestComponent>
{
public:
	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CTestComponent>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CTestComponent>>& targetComponent) override;
};

}
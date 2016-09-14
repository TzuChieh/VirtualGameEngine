#pragma once

#include "Resource/World/Event/TComponentListener.h"

namespace ve
{

class CTestComponent;

class TestComponentProcessor : public TComponentListener<CTestComponent>
{
public:
	virtual ~TestComponentProcessor() override;

	virtual void onComponentAdded(CTestComponent* component, const ComponentIndexType index) override;
	virtual void onComponentRemoval(CTestComponent* component, const ComponentIndexType index) override;
};

}
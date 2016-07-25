#pragma once

#include "Component.h"
#include "Common/type.h"

namespace xe
{

class CTestComponent : public Component
{
public:
	CTestComponent();
	CTestComponent(const CTestComponent& other);
	CTestComponent(CTestComponent&& other);
	virtual ~CTestComponent() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;
	
	//CTestComponent& operator = (CTestComponent left);
};

}
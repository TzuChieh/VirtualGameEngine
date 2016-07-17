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

	virtual void update(float32 deltaS) override;
	virtual void addToEngine(Engine* engine) override;
	
	//CTestComponent& operator = (CTestComponent left);
};

}
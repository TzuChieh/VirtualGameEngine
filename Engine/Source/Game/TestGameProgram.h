#pragma once

#include "GameProgram.h"
#include "Resource/Component/TContinuousMemoryComponentManager.h"
#include "Resource/Component/CTestComponent.h"

#include <vector>

namespace xe
{

class Component;
class CTestComponent;

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

	virtual void addTestComponent(CTestComponent&& testComponent) override;

	virtual inline Scene* getScene() override
	{
		return m_scene;
	}

private:
	Scene* m_scene;
	TContinuousMemoryComponentManager<CTestComponent> m_testComponentManager;

	virtual bool init(Engine* engine) override;
	virtual void update() override;
	virtual void decompose() override;
};

}
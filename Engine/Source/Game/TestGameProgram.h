#pragma once

#include "GameProgram.h"
#include "Resource/Component/CTestComponent.h"
#include "Resource/Component/TIndexedComponentManager.h"

#include <vector>

namespace xe
{

class Component;
class CTestComponent;

class TestGameProgram : public GameProgram
{
public:
	virtual ~TestGameProgram() override;

	virtual std::shared_ptr<ComponentHandle> addTestComponent(const CTestComponent& testComponent) override;
	virtual void removeTestComponent(std::shared_ptr<ComponentHandle> testComponentHandle) override;

	virtual inline Scene* getScene() override
	{
		return m_scene;
	}

private:
	Scene* m_scene;
	
	TIndexedComponentManager<CTestComponent> m_testComponents;

	virtual bool init(Engine* engine) override;
	virtual void update() override;
	virtual void decompose() override;
};

}
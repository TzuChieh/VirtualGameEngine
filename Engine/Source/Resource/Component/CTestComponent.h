#pragma once

#include "Component.h"
#include "Common/type.h"

#include <string>

namespace xe
{

class Engine;

class CTestComponent : public Component
{
public:
	CTestComponent();
	CTestComponent(const std::string& message);
	CTestComponent(const CTestComponent& other);
	CTestComponent(CTestComponent&& other);
	virtual ~CTestComponent() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	std::string getMessage() const;
	void setMessage(const std::string& message);
	
	//CTestComponent& operator = (CTestComponent left);

private:
	std::string m_message;
	Engine* m_engine;
};

}
#pragma once

#include "Component.h"
#include "Common/type.h"

#include <string>

namespace ve
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

	virtual ComponentTypeId getTypeId() override;

	std::string getMessage() const;
	void setMessage(const std::string& message);
	
	CTestComponent& operator = (const CTestComponent& rhs) = default;

private:
	std::string m_message;
};

}
#pragma once

#include "Resource/Component/Component.h"
#include "Resource/Component/ComponentHandle.h"

namespace xe
{

class CCamera : public Component
{
public:
	virtual ~CCamera() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

private:
};

}
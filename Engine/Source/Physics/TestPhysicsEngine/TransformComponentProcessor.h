#pragma once

#include "Resource/World/Event/TComponentListener.h"

namespace ve
{

class CTransform;

class TransformComponentProcessor final : public TComponentListener<CTransform>
{
public:
	TransformComponentProcessor();
	virtual ~TransformComponentProcessor() override;

	virtual void onComponentAdded(CTransform* component, const ComponentIndexType index) override;
	virtual void onComponentRemoval(CTransform* component, const ComponentIndexType index) override;
};

}
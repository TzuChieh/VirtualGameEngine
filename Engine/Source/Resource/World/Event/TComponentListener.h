#pragma once

#include "Resource/World/Component/ComponentIndexType.h"

namespace ve
{

template<typename ComponentType>
class TComponentListener
{
public:
	virtual ~TComponentListener() = 0;

	virtual void onComponentAdded(ComponentType* component, const ComponentIndexType index) = 0;
	virtual void onComponentRemoval(ComponentType* component, const ComponentIndexType index) = 0;
};

// Implementations:

template<typename ComponentType>
TComponentListener<ComponentType>::~TComponentListener() = default;

}// end namespace ve
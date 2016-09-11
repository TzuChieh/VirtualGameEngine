#pragma once

#include "TTypedComponentHandle.h"

#include <memory>

namespace ve
{

template <typename ComponentType>
class TComponentManagerActionListener
{
public:
	virtual ~TComponentManagerActionListener() = 0;

	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent) = 0;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent) = 0;
};

}

template<typename ComponentType>
ve::TComponentManagerActionListener<ComponentType>::~TComponentManagerActionListener() = default;
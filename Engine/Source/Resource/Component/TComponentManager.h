#pragma once

#include "Common/type.h"

#include <memory>

namespace xe
{

template<typename ComponentType>
class TComponentManager
{
public:
	virtual void updateComponents(float32 deltaS) = 0;

	virtual void addComponent(ComponentType&& component) = 0;

private:
};

}
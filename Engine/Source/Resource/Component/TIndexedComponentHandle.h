#pragma once

#include "ComponentHandle.h"
#include "TIndexedComponentManager.h"
#include "Common/type.h"

namespace xe
{

template<typename ComponentType>
class TIndexedComponentHandle : public ComponentHandle
{
public:
	TIndexedComponentHandle(TIndexedComponentManager<ComponentType>* indexedComponentManager, uint32 componentIndex)
		: m_indexedComponentManager(indexedComponentManager), m_componentIndex(componentIndex)
	{

	}

	virtual Component* getComponent() override
	{
		return static_cast<Component*>(m_indexedComponentManager->getComponent(m_componentIndex));
	}

private:
	TIndexedComponentManager<ComponentType>* m_indexedComponentManager;
	uint32 m_componentIndex;
};

}
#pragma once

#include "Common/logging.h"
#include "ComponentIndexType.h"
#include "Resource/World/TComponentStorage.h"

DECLARE_LOG_SENDER_EXTERN(TComponentHandle);

namespace ve
{

template<typename ComponentType>
class TComponentHandle
{
public:
	TComponentHandle(TComponentStorage<ComponentType>* const componentStorage, const ComponentIndexType index);

	ComponentType* operator -> ();

private:
	TComponentStorage<ComponentType>* m_componentStorage;
	ComponentIndexType                m_index;
};

// Implementations:

template<typename ComponentType>
TComponentHandle<ComponentType>::TComponentHandle(TComponentStorage<ComponentType>* const componentStorage,
                                                  const ComponentIndexType index) :
	m_componentStorage(componentStorage), m_index(index)
{

}

template<typename ComponentType>
ComponentType* TComponentHandle<ComponentType>::operator -> ()
{
	return &((*m_componentStorage)[m_index]);
}

}// end namespace ve
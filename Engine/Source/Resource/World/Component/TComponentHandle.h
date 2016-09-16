#pragma once

#include "Common/logging.h"
#include "ComponentIndexType.h"
#include "Resource/World/TComponentStorage.h"

DECLARE_LOG_SENDER_EXTERN(TComponentHandle);

namespace ve
{

template<typename ComponentType>
class TComponentHandle final
{
public:
	TComponentHandle();
	TComponentHandle(TComponentStorage<ComponentType>* const componentStorage, const ComponentIndexType index);
	TComponentHandle(const TComponentHandle<ComponentType>& other) = default;

	bool isValid() const;

	void makeInvalid();
	ComponentType* getComponent();

	ComponentType* operator -> ();
	TComponentHandle<ComponentType>& operator = (const TComponentHandle<ComponentType>& rhs) = default;

private:
	TComponentStorage<ComponentType>* m_componentStorage;
	ComponentIndexType                m_index;
};

// Implementations:

template<typename ComponentType>
TComponentHandle<ComponentType>::TComponentHandle() :
	m_componentStorage(nullptr), m_index(-1)
{

}

template<typename ComponentType>
TComponentHandle<ComponentType>::TComponentHandle(TComponentStorage<ComponentType>* const componentStorage,
                                                  const ComponentIndexType index) :
	m_componentStorage(componentStorage), m_index(index)
{
	// TODO: check if valid & nullptr
}

template<typename ComponentType>
bool TComponentHandle<ComponentType>::isValid() const
{
	return m_index >= 0;
}

template<typename ComponentType>
void TComponentHandle<ComponentType>::makeInvalid()
{
	m_index = -1;
}

template<typename ComponentType>
ComponentType* TComponentHandle<ComponentType>::getComponent()
{
	return &((*m_componentStorage)[m_index]);
}

template<typename ComponentType>
ComponentType* TComponentHandle<ComponentType>::operator -> ()
{
	return getComponent();
}

}// end namespace ve
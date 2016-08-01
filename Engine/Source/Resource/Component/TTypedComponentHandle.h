#pragma once

#include "ComponentHandle.h"

#include <memory>

namespace xe
{

class Component;

template<typename ComponentType>
class TTypedComponentHandle : public ComponentHandle
{
public:
	TTypedComponentHandle() = default;
	explicit TTypedComponentHandle(const std::shared_ptr<ComponentHandle>& componentHandle);

	virtual Component* getComponent() override;
	virtual void removeComponent() override;

	ComponentType* getTypedComponent();
	void release();
	bool isValid() const;

	ComponentType* operator -> ();

private:
	std::shared_ptr<ComponentHandle> m_componentHandle;
};

// implementations:

template<typename ComponentType>
TTypedComponentHandle<ComponentType>::TTypedComponentHandle(const std::shared_ptr<ComponentHandle>& componentHandle)
	: m_componentHandle(componentHandle)
{
	// TODO: check type
}

template<typename ComponentType>
Component* TTypedComponentHandle<ComponentType>::getComponent()
{
	return m_componentHandle->getComponent();
}

template<typename ComponentType>
void TTypedComponentHandle<ComponentType>::removeComponent()
{
	m_componentHandle->removeComponent();
}

template<typename ComponentType>
ComponentType* TTypedComponentHandle<ComponentType>::getTypedComponent()
{
	return static_cast<ComponentType*>(m_componentHandle->getComponent());
}

template<typename ComponentType>
void TTypedComponentHandle<ComponentType>::release()
{
	m_componentHandle.reset();
}

template<typename ComponentType>
bool TTypedComponentHandle<ComponentType>::isValid() const
{
	return m_componentHandle.use_count() != 0L;
}

template<typename ComponentType>
ComponentType* TTypedComponentHandle<ComponentType>::operator -> ()
{
	return getTypedComponent();
}

}
#pragma once

#include "Component.h"
#include "ComponentHandle.h"
#include "Common/logging.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(TTypedComponentHandle);

namespace ve
{

class Component;

template<typename ComponentType>
class TTypedComponentHandle : public ComponentHandle
{
public:
	explicit TTypedComponentHandle(const std::shared_ptr<ComponentHandle>& componentHandle);

	virtual Component* getComponent() override;
	virtual void removeComponent() override;

	ComponentType* getTypedComponent();
	void relinquish();
	bool isValid() const;

	ComponentType* operator -> ();

private:
	std::shared_ptr<ComponentHandle> m_componentHandle;
};

// implementations:

template<typename ComponentType>
TTypedComponentHandle<ComponentType>::TTypedComponentHandle(const std::shared_ptr<ComponentHandle>& componentHandle) : 
	m_componentHandle(componentHandle)
{
	// TODO: able to disable if-check in release build

	if(componentHandle == nullptr)
	{
		ENGINE_LOG(TTypedComponentHandle, LogLevel::NOTE_WARNING, "internal ComponentHandle is null");
	}
	else
	{
		if(componentHandle->getComponent()->getTypeId() != Component::getTypeId<ComponentType>())
		{
			ENGINE_LOG(TTypedComponentHandle, LogLevel::NOTE_WARNING, "internal ComponentHandle type mismatch");
		}
	}
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
	relinquish();
}

template<typename ComponentType>
void TTypedComponentHandle<ComponentType>::relinquish()
{
	m_componentHandle.reset();
}

template<typename ComponentType>
ComponentType* TTypedComponentHandle<ComponentType>::getTypedComponent()
{
	return static_cast<ComponentType*>(m_componentHandle->getComponent());
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
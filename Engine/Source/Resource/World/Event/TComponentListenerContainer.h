#pragma once

#include "Resource/World/Event/TComponentListener.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Common/logging.h"

#include <vector>
#include <algorithm>
#include <iostream>

DECLARE_LOG_SENDER_EXTERN(TComponentListenerContainer);

// TODO: the ability to let listeners remove listener(s) in callback methods

namespace ve
{

template<typename ComponentType>
class TComponentListenerContainer final
{
public:
	static void addListener(TComponentListener<ComponentType>* listener);
	static void removeListener(TComponentListener<ComponentType>* listener);

	static void notifyAllOnComponentAdded(ComponentType* component, const ComponentIndexType index);
	static void notifyAllOnComponentRemoval(ComponentType* component, const ComponentIndexType index);

private:
	static std::vector<TComponentListener<ComponentType>*> listeners;


};

// Implementations:

template<typename ComponentType>
std::vector<TComponentListener<ComponentType>*> TComponentListenerContainer<ComponentType>::listeners;

template<typename ComponentType>
void TComponentListenerContainer<ComponentType>::addListener(TComponentListener<ComponentType>* listener)
{
	if(listener == nullptr)
	{
		ENGINE_LOG(TComponentListenerContainer, LogLevel::NOTE_WARNING, "listener is null");
		return;
	}

	if(std::find(listeners.begin(), listeners.end(), listener) != listeners.end())
	{
		ENGINE_LOG(TComponentListenerContainer, LogLevel::NOTE_WARNING, "listener already added");
		return;
	}

	listeners.push_back(listener);

	std::cout << "listener added" << std::endl;
}

template<typename ComponentType>
void TComponentListenerContainer<ComponentType>::removeListener(TComponentListener<ComponentType>* listener)
{
	if(listener == nullptr)
	{
		ENGINE_LOG(TComponentListenerContainer, LogLevel::NOTE_WARNING, "listener is null");
		return;
	}

	auto removePosition = std::find(listeners.begin(), listeners.end(), listener);
	if(removePosition != listeners.end())
	{
		listeners.erase(removePosition);
	}
	else
	{
		ENGINE_LOG(TComponentListenerContainer, LogLevel::NOTE_WARNING, "listener not found");
		return;
	}

	std::cout << "listener removed" << std::endl;
}

template<typename ComponentType>
void TComponentListenerContainer<ComponentType>::notifyAllOnComponentAdded(ComponentType* component, const ComponentIndexType index)
{
	for(auto& listener : listeners)
	{
		listener->onComponentAdded(component, index);
	}
}

template<typename ComponentType>
void TComponentListenerContainer<ComponentType>::notifyAllOnComponentRemoval(ComponentType* component, const ComponentIndexType index)
{
	for(auto& listener : listeners)
	{
		listener->onComponentRemoval(component, index);
	}
}

}// end namespace ve
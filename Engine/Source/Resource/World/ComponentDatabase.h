#pragma once

#include "Resource/World/Component/Component.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Entity/Entity.h"
#include "Resource/World/Entity/EntityId.h"
#include "Common/logging.h"
#include "Resource/World/TComponentStorage.h"
#include "Resource/World/Component/TComponentHandle.h"
#include "Resource/World/EntityDatabase.h"
#include "Resource/World/Component/ComponentTypeId.h"

#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <string>

DECLARE_LOG_SENDER_EXTERN(ComponentDatabase);

namespace ve
{

class ComponentDatabase final
{
public:
	ComponentDatabase();

	// Manipulate component storage
	//
		template<typename ComponentType>
		ComponentIndexType addComponent(const ComponentType& component);

		template<typename ComponentType>
		bool removeComponent(const ComponentIndexType index);

		bool removeComponent(const ComponentTypeId typeId, const ComponentIndexType index);

		template<typename ComponentType>
		ComponentType& getComponent(const ComponentIndexType index);

		template<typename ComponentType>
		bool allocateComponentStorage();

		template<typename ComponentType>
		TComponentStorage<ComponentType>* getComponentStorage();

		template<typename ComponentType>
		TComponentHandle<ComponentType> getComponentHandle(const ComponentIndexType index) const;

	// forbid copying
	ComponentDatabase(const ComponentDatabase& other) = delete;
	ComponentDatabase& operator = (const ComponentDatabase& rhs) = delete;

private:
	std::array<std::shared_ptr<void>, Entity::MAX_COMPONENTS> m_componentStorages;
	EntityComponentIndexMap m_entityComponentIndexMap;
};

// Implementations:

template<typename ComponentType>
bool ComponentDatabase::allocateComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(m_componentStorages[typeId])
	{
		ENGINE_LOG(ComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " already allocated");
		return false;
	}

	m_componentStorages[typeId] = std::make_shared<TComponentStorage<ComponentType>>();
	return true;
}

template<typename ComponentType>
TComponentStorage<ComponentType>* ComponentDatabase::getComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(!m_componentStorages[typeId])
	{
		ENGINE_LOG(ComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " not allocated yet");
	}

	return static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());
}

template<typename ComponentType>
ComponentIndexType ComponentDatabase::addComponent(const ComponentType& component)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	const std::size_t index = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get())->add(component);
	return static_cast<ComponentIndexType>(index);
}

template<typename ComponentType>
bool ComponentDatabase::removeComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	return static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get())->remove(static_cast<std::size_t>(index));
}

template<typename ComponentType>
ComponentType& ComponentDatabase::getComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	auto* componentStorage = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());
	return (*componentStorage)[static_cast<std::size_t>(index)];
}

template<typename ComponentType>
TComponentHandle<ComponentType> ComponentDatabase::getComponentHandle(const ComponentIndexType index) const
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(!m_componentStorages[typeId])
	{
		ENGINE_LOG(ComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " not allocated yet");
		return TComponentHandle<ComponentType>();
	}

	auto* componentStorage = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());

	return TComponentHandle<ComponentType>(componentStorage, index);
}

}// end namespace ve;
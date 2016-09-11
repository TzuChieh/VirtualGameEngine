#pragma once

#include "Resource/World/Component/Component.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Entity/Entity.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/Entity/EntityComponentIndexMap.h"
#include "Common/logging.h"
#include "Utility/TStableIndexDenseArray.h"

#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <string>

DECLARE_LOG_SENDER_EXTERN(EntityComponentDatabase);

namespace ve
{

class EntityComponentDatabase final
{
public:
	template<typename T>
	using ComponentStorageType = TStableIndexDenseArray<T>;

public:
	EntityComponentDatabase();

	// Map each entity to their attached components.
	//
		void initComponentsIndexMapping(const EntityId::IndexType entityIndex);

		template<typename ComponentType>
		void mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index);

		template<typename ComponentType>
		void unmapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index);

		template<typename ComponentType>
		ComponentIndexType getMappedComponentIndex(const EntityId::IndexType entityIndex);

	// Manipulate component storage
	//
		template<typename ComponentType>
		ComponentIndexType addComponent(const ComponentType& component);

		template<typename ComponentType>
		bool removeComponent(const ComponentIndexType index);

		template<typename ComponentType>
		ComponentType& getComponent(const ComponentIndexType index);

		template<typename ComponentType>
		bool allocateComponentStorage();

		template<typename ComponentType>
		ComponentStorageType<ComponentType>* getComponentStorage();

	// forbid copying
	EntityComponentDatabase(const EntityComponentDatabase& other) = delete;
	EntityComponentDatabase& operator = (const EntityComponentDatabase& rhs) = delete;

private:
	std::array<std::shared_ptr<void>, Entity::MAX_COMPONENTS> m_componentStorages;
	EntityComponentIndexMap m_entityComponentIndexMap;
};

// Implementations:

template<typename ComponentType>
void EntityComponentDatabase::mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index)
{
	m_entityComponentIndexMap.map<ComponentType>(entityIndex, index);
}

template<typename ComponentType>
void EntityComponentDatabase::unmapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index)
{
	m_entityComponentIndexMap.unmap<ComponentType>(entityIndex);
}

template<typename ComponentType>
ComponentIndexType EntityComponentDatabase::getMappedComponentIndex(const EntityId::IndexType entityIndex)
{
	return m_entityComponentIndexMap.get<ComponentType>(entityIndex);
}

template<typename ComponentType>
bool EntityComponentDatabase::allocateComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(m_componentStorages[typeId])
	{
		ENGINE_LOG(EntityComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " already allocated");
		return false;
	}

	m_componentStorages[typeId] = std::make_shared<ComponentStorageType<ComponentType>>();
	return true;
}

template<typename ComponentType>
EntityComponentDatabase::ComponentStorageType<ComponentType>* EntityComponentDatabase::getComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(!m_componentStorages[typeId])
	{
		ENGINE_LOG(EntityComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " not allocated yet");
	}

	return static_cast<ComponentStorageType<ComponentType>*>(m_componentStorages[typeId].get());
}

template<typename ComponentType>
ComponentIndexType EntityComponentDatabase::addComponent(const ComponentType& component)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	const std::size_t index = static_cast<ComponentStorageType<ComponentType>*>(m_componentStorages[typeId].get())->add(component);
	return static_cast<ComponentIndexType>(index);
}

template<typename ComponentType>
bool EntityComponentDatabase::removeComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	return static_cast<ComponentStorageType<ComponentType>*>(m_componentStorages[typeId].get())->remove(static_cast<std::size_t>(index));
}

template<typename ComponentType>
ComponentType& EntityComponentDatabase::getComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	auto& componentStorage = *(static_cast<ComponentStorageType<ComponentType>*>(m_componentStorages[typeId].get()));
	return componentStorage[static_cast<std::size_t>(index)];
}

}// end namespace ve;
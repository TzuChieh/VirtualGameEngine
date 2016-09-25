#pragma once

#include "Common/type.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Component/Component.h"
#include "Resource/World/Entity/EntityId.h"

#include <utility>
#include <vector>

namespace ve
{

class EntityComponentIndexMap
{
public:
	static const ComponentIndexType UNMAPPED_VALUE = -1;

public:
	void initMapping(const EntityId entityId);

	template<typename ComponentType>
	void map(const EntityId entityId, const ComponentIndexType componentIndex);

	template<typename ComponentType>
	void unmap(const EntityId entityId);

	template<typename ComponentType>
	ComponentIndexType get(const EntityId entityId) const;

private:
	std::vector<ComponentIndexType> m_map;

	std::size_t getHeadIndex(const EntityId entityId) const;
	void clearMapping(const std::size_t mapIndex);
};

// Implementations:

template<typename ComponentType>
void EntityComponentIndexMap::map(const EntityId entityId, const ComponentIndexType componentIndex)
{
	m_map[getHeadIndex(entityId) + Component::getTypeId<ComponentType>()] = static_cast<ComponentIndexType>(componentIndex);
}

template<typename ComponentType>
void EntityComponentIndexMap::unmap(const EntityId entityId)
{
	clearMapping(getHeadIndex(entityId) + Component::getTypeId<ComponentType>());
}

template<typename ComponentType>
ComponentIndexType EntityComponentIndexMap::get(const EntityId entityId) const
{
	return m_map[getHeadIndex(entityId) + Component::getTypeId<ComponentType>()];
}

}// end namespace ve
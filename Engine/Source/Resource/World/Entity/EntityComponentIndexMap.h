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
	void initMapping(const EntityId::IndexType entityIndex);

	template<typename ComponentType>
	void map(const EntityId::IndexType entityIndex, const ComponentIndexType componentIndex);

	template<typename ComponentType>
	void unmap(const EntityId::IndexType entityIndex);

	template<typename ComponentType>
	ComponentIndexType get(const EntityId::IndexType entityIndex) const;

private:
	std::vector<ComponentIndexType> m_map;

	std::size_t getHeadIndex(const EntityId::IndexType entityIndex) const;
	void clearMapping(const std::size_t mapIndex);
};

// Implementations:

template<typename ComponentType>
void EntityComponentIndexMap::map(const EntityId::IndexType entityIndex, const ComponentIndexType componentIndex)
{
	m_map[getHeadIndex(entityIndex) + Component::getTypeId<ComponentType>()] = static_cast<ComponentIndexType>(componentIndex);
}

template<typename ComponentType>
void EntityComponentIndexMap::unmap(const EntityId::IndexType entityIndex)
{
	clearMapping(getHeadIndex(entityIndex) + Component::getTypeId<ComponentType>());
}

template<typename ComponentType>
ComponentIndexType EntityComponentIndexMap::get(const EntityId::IndexType entityIndex) const
{
	return m_map[getHeadIndex(entityIndex) + Component::getTypeId<ComponentType>()];
}

}// end namespace ve
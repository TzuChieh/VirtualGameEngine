#include "EntityComponentIndexMap.h"
#include "Resource/World/Entity/Entity.h"

namespace ve
{

void EntityComponentIndexMap::initMapping(const EntityId entityId)
{
	const std::size_t headIndex = getHeadIndex(entityId);
	const std::size_t tailIndex = headIndex + Entity::MAX_COMPONENTS - 1;

	if(headIndex + Entity::MAX_COMPONENTS > m_map.size())
	{
		m_map.resize((entityId + 1) * Entity::MAX_COMPONENTS);
	}

	for(std::size_t i = headIndex; i <= tailIndex; i++)
	{
		clearMapping(i);
	}
}

std::size_t EntityComponentIndexMap::getHeadIndex(const EntityId entityId) const
{
	return entityId * Entity::MAX_COMPONENTS;
}

void EntityComponentIndexMap::clearMapping(const std::size_t mapIndex)
{
	m_map[mapIndex] = INVALID_COMPONENT_INDEX;
}

}// end namespace ve
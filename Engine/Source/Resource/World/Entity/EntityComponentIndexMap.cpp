#include "EntityComponentIndexMap.h"
#include "Resource/World/Entity/Entity.h"

#define UNMAP_VALUE -1

namespace ve
{

void EntityComponentIndexMap::initMapping(const EntityId::IndexType entityIndex)
{
	const std::size_t headIndex = getHeadIndex(entityIndex);
	const std::size_t tailIndex = headIndex + Entity::MAX_COMPONENTS - 1;

	if(headIndex + Entity::MAX_COMPONENTS > m_map.size())
	{
		m_map.resize((entityIndex + 1) * Entity::MAX_COMPONENTS);
	}

	for(std::size_t i = headIndex; i <= tailIndex; i++)
	{
		clearMapping(i);
	}
}

std::size_t EntityComponentIndexMap::getHeadIndex(const EntityId::IndexType entityIndex) const
{
	return entityIndex * Entity::MAX_COMPONENTS;
}

void EntityComponentIndexMap::clearMapping(const std::size_t mapIndex)
{
	m_map[mapIndex] = UNMAP_VALUE;
}

}// end namespace ve
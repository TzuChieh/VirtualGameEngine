#include "EntityComponentDatabase.h"

DEFINE_LOG_SENDER(EntityComponentDatabase);

namespace ve
{

EntityComponentDatabase::EntityComponentDatabase() = default;

void EntityComponentDatabase::initComponentsIndexMapping(const EntityId::IndexType entityIndex)
{
	m_entityComponentIndexMap.initMapping(entityIndex);
}

}// end namespace ve
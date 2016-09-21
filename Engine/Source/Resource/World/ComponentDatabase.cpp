#include "ComponentDatabase.h"

DEFINE_LOG_SENDER(ComponentDatabase);

namespace ve
{

ComponentDatabase::ComponentDatabase() = default;

void ComponentDatabase::initComponentsIndexMapping(const EntityId::IndexType entityIndex)
{
	m_entityComponentIndexMap.initMapping(entityIndex);
}

}// end namespace ve
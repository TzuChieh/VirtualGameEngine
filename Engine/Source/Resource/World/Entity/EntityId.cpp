#include "EntityId.h"

using namespace ve;

EntityId::SerialType EntityId::invalidSerial = 0U;

EntityId::EntityId()
	: m_index(0U), m_serial(invalidSerial)
{

}

EntityId::EntityId(const IndexType index, const SerialType serial)
	: m_index(index), m_serial(serial)
{

}

EntityId::EntityId(const EntityId& other)
	: m_index(other.m_index), m_serial(other.m_serial)
{

}
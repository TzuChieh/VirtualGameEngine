#include "EntityIdentifier.h"

using namespace ve;

EntitySerial EntityIdentifier::invalidSerial = 0U;

EntityIdentifier::EntityIdentifier()
	: m_id(0U), m_serial(invalidSerial)
{

}

EntityIdentifier::EntityIdentifier(const EntityId id, const EntitySerial serial)
	: m_id(id), m_serial(serial)
{

}

EntityIdentifier::EntityIdentifier(const EntityIdentifier& other)
	: m_id(other.m_id), m_serial(other.m_serial)
{

}
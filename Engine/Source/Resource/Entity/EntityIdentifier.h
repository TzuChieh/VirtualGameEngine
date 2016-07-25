#pragma once

#include "Common/type.h"

namespace xe
{
typedef uint64 EntityId;
typedef uint64 EntitySerial;

class EntityIdentifier
{
public:
	static uint64 invalidSerial;

public:
	EntityIdentifier();
	EntityIdentifier(const EntityId id, const EntitySerial serial);
	EntityIdentifier(const EntityIdentifier& other);

	EntityId     m_id;
	EntitySerial m_serial;
};

}
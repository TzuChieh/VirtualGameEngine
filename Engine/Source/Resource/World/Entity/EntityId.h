#pragma once

#include "Common/type.h"

#include <utility>

namespace ve
{


class EntityId
{
public:
	typedef std::size_t IndexType;
	typedef uint32      SerialType;

public:
	static SerialType invalidSerial;

public:
	EntityId();
	EntityId(const IndexType index, const SerialType serial);
	EntityId(const EntityId& other);

	IndexType  m_index;
	SerialType m_serial;
};

}
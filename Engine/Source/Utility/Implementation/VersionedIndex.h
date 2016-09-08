#pragma once

#include "Common/type.h"

#include <cstddef>

namespace ve
{

class VersionedIndex
{
public:
	static const std::size_t INDEX_INITIAL_VALUE   = 0;
	static const uint32      VERSION_INITIAL_VALUE = 0;

public:
	VersionedIndex() : 
		index(INDEX_INITIAL_VALUE), version(VERSION_INITIAL_VALUE)
	{

	}

	std::size_t index;
	uint32      version;
};

}
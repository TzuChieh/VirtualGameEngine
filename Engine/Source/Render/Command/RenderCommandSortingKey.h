#pragma once

#include "Common/type.h"

#include <vector>

namespace ve
{

typedef uint64 RenderCommandSortingKey;

class KeyComparator
{
public:
	KeyComparator(const std::vector<RenderCommandSortingKey>* keys) : 
		m_keys(keys)
	{

	}

	inline bool operator () (std::size_t a, std::size_t b)
	{
		return (*m_keys)[a] < (*m_keys)[b];
	}

private:
	const std::vector<RenderCommandSortingKey>* m_keys;
};

}
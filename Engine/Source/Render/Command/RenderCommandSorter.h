#pragma once

#include "GpuCommand.h"
#include "RenderCommandSortingKey.h"
#include "SortingStrategy.h"

#include <utility>
#include <vector>

namespace ve
{

class RenderCommandInfo;
class GpuCommandQueue;

class RenderCommandSorter final
{
public:
	RenderCommandSorter(const ESortingStrategy& sortingStrategy);

	void sort(const std::vector<std::pair<GpuCommand, RenderCommandInfo>>& commandInfoPairs, 
	          GpuCommandQueue* out_commandQueue) const;

private:
	SortingStrategy m_sortingStrategy;

	mutable std::vector<RenderCommandSortingKey> m_keyCache;
	mutable std::vector<std::size_t> m_indexCache;
};

}
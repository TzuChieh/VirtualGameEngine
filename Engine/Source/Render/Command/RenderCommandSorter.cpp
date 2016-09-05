#include "RenderCommandSorter.h"
#include "GpuCommandQueue.h"
#include "RenderCommandInfo.h"

#include <algorithm>

using namespace ve;

RenderCommandSorter::RenderCommandSorter(const ESortingStrategy& sortingStrategy) : 
	m_sortingStrategy(SortingStrategy::getSortingStrategy(sortingStrategy))
{

}

void RenderCommandSorter::addCommand(const GpuCommand& command, const RenderCommandInfo& info)
{
	m_commandInfoPairs.push_back(CommandInfoPair(command, info));

	const std::size_t index = m_commandInfoPairs.size() - 1;
	const RenderCommandSortingKey key = m_sortingStrategy.genRenderCommandSortingKey(info);
	m_keyCache.push_back(key);
	m_indexCache.push_back(index);
}

void RenderCommandSorter::clearCommands()
{
	m_commandInfoPairs.clear();
	m_keyCache.clear();
	m_indexCache.clear();
}

void RenderCommandSorter::sortCommands() const
{
	// Sort the index cache based on the key value fetched by the index, 
	// i.e., after sorting, m_keyCache[m_indexCache[i]] will be in ascending order.
	KeyComparator keyComparator(&m_keyCache);
	std::sort(m_indexCache.begin(), m_indexCache.end(), keyComparator);
}

// If sortCommands() was called before this method get called, then the queued
// commands' order will be optimal based on the specified sorting strategy; otherwise
// the order will be the same as how they are added (FIFO).
void RenderCommandSorter::queueCommands(GpuCommandQueue* out_commandQueue) const
{
	for(const std::size_t index : m_indexCache)
	{
		out_commandQueue->queue(m_commandInfoPairs[index].first);
	}
}
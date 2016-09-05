#include "RenderCommandSorter.h"
#include "GpuCommandQueue.h"
#include "RenderCommandInfo.h"

#include <algorithm>

using namespace ve;

RenderCommandSorter::RenderCommandSorter(const ESortingStrategy& sortingStrategy) : 
	m_sortingStrategy(SortingStrategy::getSortingStrategy(sortingStrategy))
{

}

void RenderCommandSorter::sort(const std::vector<std::pair<GpuCommand, RenderCommandInfo>>& commandInfoPairs,
                               GpuCommandQueue* out_commandQueue) const
{
	m_keyCache.clear();
	m_indexCache.clear();

	// Gather sorting keys and their corresponding indices.
	const std::size_t numCommandInfoPairs = commandInfoPairs.size();
	for(std::size_t i = 0; i < numCommandInfoPairs; i++)
	{
		const RenderCommandSortingKey key = m_sortingStrategy.genRenderCommandSortingKey(commandInfoPairs[i].second);
		m_keyCache.push_back(key);
		m_indexCache.push_back(i);
	}

	// Sort the index cache based on the key value fetched by the index, 
	// i.e., after sorting, m_keyCache[m_indexCache[i]] will be in ascending order.
	KeyComparator keyComparator(&m_keyCache);
	std::sort(m_indexCache.begin(), m_indexCache.end(), keyComparator);

	// Now the index cache contains the optimal index order for queueing render commands
	// based on the specified sorting strategy.
	for(const std::size_t sortedIndex : m_indexCache)
	{
		out_commandQueue->queue(commandInfoPairs[sortedIndex].first);
	}
}
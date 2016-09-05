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

	void addCommand(const GpuCommand& command, const RenderCommandInfo& info);
	void clearCommands();

	void sortCommands() const;

	void queueCommands(GpuCommandQueue* out_commandQueue) const;

private:
	typedef std::pair<GpuCommand, RenderCommandInfo> CommandInfoPair;

	SortingStrategy m_sortingStrategy;

	std::vector<CommandInfoPair> m_commandInfoPairs;
	mutable std::vector<RenderCommandSortingKey> m_keyCache;
	mutable std::vector<std::size_t> m_indexCache;
};

}
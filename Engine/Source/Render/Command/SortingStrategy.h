#pragma once

#include "Common/type.h"
#include "RenderCommandSortingKey.h"
#include "SubkeyEntry.h"
#include "Render/Core/GLResourceId.h"
#include "Common/logging.h"

#include <utility>
#include <array>

DECLARE_LOG_SENDER_EXTERN(SortingStrategy);

namespace ve
{

enum class ESortingStrategy : int32;
class RenderCommandInfo;

class SortingStrategy final
{
public:
	static SortingStrategy getSortingStrategy(const ESortingStrategy strategy);

public:
	SortingStrategy();

	RenderCommandSortingKey genRenderCommandSortingKey(const RenderCommandInfo& info) const;

private:
	typedef std::pair<int32, int32> BitRange;

	std::array<BitRange, static_cast<std::size_t>(ESubkeyEntry::MAX_ENTRY) + 1> m_subkeyBitRanges;

	bool isSubkeyUsed(const ESubkeyEntry subkeyEntry) const;
	const BitRange& getBitRange(const ESubkeyEntry subkeyEntry) const;
	void setBitRange(const ESubkeyEntry subkeyEntry, const int32 minBit, const int32 maxBit);

	void encodeMaterialId(const RenderCommandInfo& info, RenderCommandSortingKey* key) const;

	static uint64 getBitRangeMaxValue(const BitRange& bitRange);
	static uint64 genBitMask(const BitRange& bitRange);
	static void encodeSubkey(const uint32 subkey, const BitRange& bitRange, RenderCommandSortingKey* key);
};

enum class ESortingStrategy : int32
{
	NO_SORTING, 
	PRIORITIED_MATERIAL_ONLY
};

}
#include "SortingStrategy.h"
#include "RenderCommandInfo.h"

#include <bitset>
#include <iostream>

#define BIT_RANGE_NOT_USED -1

DEFINE_LOG_SENDER(SortingStrategy);

using namespace ve;

SortingStrategy SortingStrategy::getSortingStrategy(const ESortingStrategy strategy)
{
	switch(strategy)
	{
	case ESortingStrategy::NO_SORTING:
		return SortingStrategy();

	case ESortingStrategy::PRIORITIED_MATERIAL_ONLY:
		SortingStrategy sortingStrategy;
		sortingStrategy.setBitRange(ESubkeyEntry::MATERIAL_ID, 45, 55);
		return sortingStrategy;
	}
}

SortingStrategy::SortingStrategy()
{
	for(std::size_t i = 0; i <= static_cast<std::size_t>(ESubkeyEntry::MAX_ENTRY); i++)
	{
		m_subkeyBitRanges[i].first = BIT_RANGE_NOT_USED;
		m_subkeyBitRanges[i].second = BIT_RANGE_NOT_USED;
	}
}

RenderCommandSortingKey SortingStrategy::genRenderCommandSortingKey(const RenderCommandInfo& info) const
{
	const std::size_t numKeyBits = sizeof(RenderCommandSortingKey) * 8;
	RenderCommandSortingKey key = 0;

	encodeMaterialId(info, &key);

	return key;
}

bool SortingStrategy::isSubkeyUsed(const ESubkeyEntry subkeyEntry) const
{
	return getBitRange(subkeyEntry).first != BIT_RANGE_NOT_USED;
}

const SortingStrategy::BitRange& SortingStrategy::getBitRange(const ESubkeyEntry subkeyEntry) const
{
	return m_subkeyBitRanges[static_cast<SubkeyEntryUnderlyingType>(subkeyEntry)];
}

void SortingStrategy::setBitRange(const ESubkeyEntry subkeyEntry, const int32 minBit, const int32 maxBit)
{
	m_subkeyBitRanges[static_cast<SubkeyEntryUnderlyingType>(subkeyEntry)].first = minBit;
	m_subkeyBitRanges[static_cast<SubkeyEntryUnderlyingType>(subkeyEntry)].second = maxBit;
}

void SortingStrategy::encodeMaterialId(const RenderCommandInfo& info, RenderCommandSortingKey* key) const
{
	if(isSubkeyUsed(ESubkeyEntry::MATERIAL_ID))
	{
		encodeSubkey(info.materialId, getBitRange(ESubkeyEntry::MATERIAL_ID), key);
	}
}

uint64 SortingStrategy::getBitRangeMaxValue(const BitRange& bitRange)
{
	const int32 usedBits = bitRange.second - bitRange.first + 1;
	return (1ULL << static_cast<uint64>(usedBits)) - 1ULL;
}

uint64 SortingStrategy::genBitMask(const BitRange& bitRange)
{
	return getBitRangeMaxValue(bitRange) << static_cast<uint64>(bitRange.first);
}

void SortingStrategy::encodeSubkey(const uint32 subkey, const BitRange& bitRange, RenderCommandSortingKey* key)
{
	if(getBitRangeMaxValue(bitRange) < subkey)
	{
		ENGINE_LOG(SortingStrategy, LogLevel::NOTE_WARNING, "subkey overflow under current strategy's bit range");
		return;
	}

	const uint64 shiftedSubkey = (static_cast<uint64>(subkey) << static_cast<uint64>(bitRange.first));

	/*std::cout << "BitRange: " << bitRange.first << " ~ " << bitRange.second << std::endl;
	std::cout << "max BitRange value: " << getBitRangeMaxValue(bitRange) << std::endl;
	std::cout << "max BitRange value (binary): " << std::bitset<64>(getBitRangeMaxValue(bitRange)) << std::endl;
	std::cout << "bitmask: " << std::bitset<64>(genBitMask(bitRange)) << std::endl;
	std::cout << "shifted subkey: " << std::bitset<64>(shiftedSubkey) << std::endl;
	std::cout << "original key: " << std::bitset<64>(*key) << std::endl;*/

	*key |= shiftedSubkey;

	//std::cout << "modified key: " << std::bitset<64>(*key) << std::endl;
}
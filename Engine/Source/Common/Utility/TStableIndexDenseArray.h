#pragma once

#include "Common/Utility/Implementation/VersionedIndex.h"
#include "Common/logging.h"

#include <vector>
#include <utility>
#include <iostream>

DECLARE_LOG_SENDER_EXTERN(TStableIndexDenseArray);

namespace ve
{

template<typename T>
class TStableIndexDenseArray
{
public:
	TStableIndexDenseArray();

	std::size_t add(const T& object);
	bool remove(const std::size_t stableIndex);

	std::size_t length() const;

	typename std::vector<T>::iterator       begin() noexcept;
	typename std::vector<T>::const_iterator begin() const noexcept;
	typename std::vector<T>::iterator       end()   noexcept;
	typename std::vector<T>::const_iterator end()   const noexcept;

	T& operator [] (const std::size_t stableIndex);
	const T& operator [] (const std::size_t stableIndex) const;

private:
	std::vector<T> m_objects;
	std::vector<std::size_t> m_objectToIndexMap;
	std::vector<std::pair<std::size_t, int8>> m_indexToObjectMapValidityPairs;
	std::vector<std::size_t> m_freeIndices;
};

// Implementations:

template<typename T>
TStableIndexDenseArray<T>::TStableIndexDenseArray() = default;

template<typename T>
std::size_t TStableIndexDenseArray<T>::add(const T& object)
{
	std::size_t stableIndex;

	if(m_freeIndices.empty())
	{
		stableIndex = m_objects.size();
		m_indexToObjectMapValidityPairs.push_back(std::make_pair(stableIndex, VGE_TRUE));
	}
	else
	{
		stableIndex = m_freeIndices.back();
		m_freeIndices.pop_back();

		m_indexToObjectMapValidityPairs[stableIndex].first = m_objects.size();
		m_indexToObjectMapValidityPairs[stableIndex].second = VGE_TRUE;
	}

	m_objects.push_back(object);
	m_objectToIndexMap.push_back(stableIndex);

	std::cout << m_indexToObjectMapValidityPairs.size() << std::endl;
	std::cout << length() << std::endl;

	return stableIndex;
}

template<typename T>
bool TStableIndexDenseArray<T>::remove(const std::size_t stableIndex)
{
	if(m_indexToObjectMapValidityPairs[stableIndex].second != VGE_TRUE)
	{
		ENGINE_LOG(TStableIndexDenseArray, LogLevel::NOTE_WARNING, "at remove(), invalid stableIndex detected");
		return false;
	}

	const std::size_t objectIndex = m_indexToObjectMapValidityPairs[stableIndex].first;
	const std::size_t lastIndex = length() - 1;

	// Swap-and-pop the target object with the last object; also copy the last object's stable
	// index to new location.
	std::swap(m_objects[objectIndex], m_objects[lastIndex]);
	m_objectToIndexMap[objectIndex] = m_objectToIndexMap[lastIndex];
	m_objects.pop_back();
	m_objectToIndexMap.pop_back();

	// Update validity.
	m_indexToObjectMapValidityPairs[stableIndex].second = VGE_FALSE;

	// Update swapped object's stable index mapping.
	m_indexToObjectMapValidityPairs[m_objectToIndexMap[objectIndex]].first = objectIndex;

	// Add freed stable index for later use.
	m_freeIndices.push_back(stableIndex);

	return true;
}

template<typename T>
T& TStableIndexDenseArray<T>::operator [] (const std::size_t stableIndex)
{
	return m_objects[m_indexToObjectMapValidityPairs[stableIndex].first];
}

template<typename T>
const T& TStableIndexDenseArray<T>::operator [] (const std::size_t stableIndex) const
{
	return m_objects[m_indexToObjectMapValidityPairs[stableIndex].first];
}

template<typename T>
std::size_t TStableIndexDenseArray<T>::length() const
{
	return m_objects.size();
}

template<typename T>
typename std::vector<T>::iterator TStableIndexDenseArray<T>::begin() noexcept
{
	return m_objects.begin();
}

template<typename T>
typename std::vector<T>::const_iterator TStableIndexDenseArray<T>::begin() const noexcept
{
	return m_objects.begin();
}

template<typename T>
typename std::vector<T>::iterator TStableIndexDenseArray<T>::end() noexcept
{
	return m_objects.begin() + length();
}

template<typename T>
typename std::vector<T>::const_iterator TStableIndexDenseArray<T>::end() const noexcept
{
	return m_objects.begin() + length();
}

}
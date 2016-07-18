#include "EntityComponentStorage.h"

using namespace xe;

EntityComponentStorage::EntityComponentStorage()
{
	for(auto& component : m_entityComponents)
	{
		component = nullptr;
	}
}


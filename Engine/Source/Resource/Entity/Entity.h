#pragma once

#include "Common/type.h"

#include <unordered_map>
#include <typeinfo>
#include <vector>
#include <memory>

namespace xe
{

class Scene;

typedef uint64 EntityId;

class Entity
{
public:
	Entity();
	Entity(const EntityId entityId, Scene* scene);

	void decompose();

private:
	EntityId m_id;
	Scene* m_scene;
};

}
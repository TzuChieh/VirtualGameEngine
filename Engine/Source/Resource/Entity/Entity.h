#pragma once

#include "Common/type.h"
#include "EntityIdentifier.h"

#include <unordered_map>
#include <typeinfo>
#include <vector>
#include <memory>

namespace xe
{
class Engine;

enum class EntityProperties : uint32
{
	MAX_COMPONENTS = 64U
};

class Entity
{
	friend class Scene;

public:
	Entity();
	Entity(const EntityIdentifier& entityIdentifier, Scene* scene);

	void removeFromScene();

private:
	EntityIdentifier m_entityIdentifier;
	Scene* m_scene;

	void addToEngine(Engine* engine);
};

}
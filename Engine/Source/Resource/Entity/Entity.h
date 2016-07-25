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
class Scene;

enum class EntityProperties : uint32
{
	MAX_COMPONENTS = 64U
};

class Entity
{
public:
	Entity();
	Entity(const EntityIdentifier& entityIdentifier, Scene* parentScene);
	Entity(const Entity& other);

	void removeFromScene();

	Scene* getParentScene() const;
	void setParentScene(Scene* parentScene);

	EntityIdentifier getEntityIdentifier() const;

private:
	EntityIdentifier m_entityIdentifier;
	Scene* m_parentScene;
};

}
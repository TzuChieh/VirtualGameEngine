#pragma once

#include "Common/type.h"
#include "EntityIdentifier.h"
//#include "Resource/Component/Component.h"

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

	template<typename ComponentType>
	ComponentType* getComponent()
	{
		if(!m_parentScene)
		{
			std::cerr << "Entity Warning: cannot retrieve component since current entity does not belong to any scene" << std::endl;
			return nullptr;
		}

		return m_parentScene->getComponent<ComponentType>(*this);
	}

	template<typename ComponentType>
	void removeComponent()
	{
		if(!m_parentScene)
		{
			std::cerr << "Entity Warning: cannot retrieve component since current entity does not belong to any scene" << std::endl;
			return;
		}

		m_parentScene->removeComponent<ComponentType>(*this);
	}

private:
	EntityIdentifier m_entityIdentifier;
	Scene* m_parentScene;
};

}
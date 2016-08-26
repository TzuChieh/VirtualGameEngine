#pragma once

#include "Common/type.h"
#include "EntityIdentifier.h"
#include "Resource/Component/types.h"
#include "Resource/Component/ComponentHandle.h"

#include <memory>
#include <iostream>

namespace ve
{

class Engine;
class Scene;

class Entity
{
public:
	static const uint32 MAX_COMPONENTS = 64;

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
		const auto& componentHandle = getComponentHandleFromParentScene(Component::getTypeId<ComponentType>());
		return componentHandle ? static_cast<ComponentType*>(componentHandle->getComponent()) : nullptr;
	}

	template<typename ComponentType>
	void removeComponent()
	{
		const auto& componentHandle = getComponentHandleFromParentScene(Component::getTypeId<ComponentType>());
		if(componentHandle)
		{
			componentHandle->removeComponent();
		}
		else
		{
			std::cout << "Entity Warning: attempting to remove a non-exist component" << std::endl;
		}
	}

private:
	EntityIdentifier m_entityIdentifier;
	Scene* m_parentScene;

	std::shared_ptr<ComponentHandle> getComponentHandleFromParentScene(ComponentTypeId typeId) const;
};

}
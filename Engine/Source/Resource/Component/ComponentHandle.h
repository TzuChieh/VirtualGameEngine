#pragma once

namespace xe
{

class Component;

class ComponentHandle
{
public:
	virtual Component* getComponent() = 0;
	virtual void removeComponent() = 0;
};

}
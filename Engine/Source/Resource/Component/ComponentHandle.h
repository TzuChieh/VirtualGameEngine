#pragma once

namespace ve
{

class Component;

class ComponentHandle
{
public:
	virtual ~ComponentHandle() = 0;

	virtual Component* getComponent() = 0;
	virtual void removeComponent() = 0;
};

}
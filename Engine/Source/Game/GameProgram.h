#pragma once

#include "Resource/Component/TComponentManager.h"

namespace xe
{

class Component;
class CTestComponent;

class GameProgram
{
	friend class Engine;

public:
	virtual ~GameProgram() = 0;

	virtual void addTestComponent(CTestComponent&& testComponent) = 0;

private:
	virtual void update() = 0;
	virtual bool init(Engine* engine) = 0;
	virtual void decompose() = 0;
};

}
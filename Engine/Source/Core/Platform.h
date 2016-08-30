#pragma once

#include "Common/type.h"

namespace ve
{

class Input;
class Timer;
class EngineProxy;

class Platform
{
public:
	virtual ~Platform() = 0;

	virtual void update() = 0;
	virtual void refresh() = 0;

	virtual bool shouldClose() = 0;

	virtual uint32 getWidthPx() const = 0;
	virtual uint32 getHeightPx() const = 0;

	virtual const Input* getInput() const = 0;
	virtual const Timer* getTimer() const = 0;
};

}
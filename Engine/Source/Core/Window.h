#pragma once

#include "Type.h"

namespace xe
{

class Window
{
public:
	virtual ~Window() = 0;

	virtual bool init() = 0;
	virtual void update() = 0;
	virtual void refresh() = 0;
	virtual void dispose() = 0;

	virtual bool shouldClose() = 0;

	virtual uint32 getWidthPx() const = 0;
	virtual uint32 getHeightPx() const = 0;
};

}
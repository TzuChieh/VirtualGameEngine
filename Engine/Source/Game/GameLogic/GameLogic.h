#pragma once

#include "Common/type.h"

namespace xe
{

class Engine;

class GameLogic
{
public:
	virtual ~GameLogic() = 0;

	virtual void execute(float32 deltaS, Engine* engine) = 0;
};

}
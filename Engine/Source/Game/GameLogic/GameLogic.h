#pragma once

#include "Common/type.h"

namespace xe
{

class GameLogic
{
public:
	virtual ~GameLogic() = 0;

	virtual void execute(float32 deltaS) = 0;
};

}
#pragma once

#include "Common/type.h"

namespace ve
{

class Timer
{
public:
	virtual float64 getCurrentTimeS() const = 0;
	virtual float64 getCurrentTimeMs() const = 0;
};

}
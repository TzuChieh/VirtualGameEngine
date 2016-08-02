#pragma once

#include "GameLogic.h"

namespace xe
{

class CameraControl : public GameLogic
{
public:
	virtual ~CameraControl() override;

	virtual void execute(float32 deltaS) override;
};

}
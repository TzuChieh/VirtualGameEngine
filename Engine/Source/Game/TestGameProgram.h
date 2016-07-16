#pragma once

#include "GameProgram.h"

#include <vector>

namespace xe
{

class Component;

class TestGameProgram : public GameProgram
{
public:
	
private:
	virtual bool init(Engine* engine) override;
	virtual void update() override;
	virtual void decompose() override;
};

}
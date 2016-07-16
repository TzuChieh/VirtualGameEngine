#pragma once

namespace xe
{

class Component;

class GameProgram
{

	friend class Engine;

public:

private:
	virtual void update() = 0;
	virtual bool init(Engine* engine) = 0;
	virtual void decompose() = 0;
};

}
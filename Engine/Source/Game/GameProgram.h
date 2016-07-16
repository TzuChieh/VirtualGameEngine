#pragma once

namespace xe {

class Component;

class GameProgram {

friend class Engine;

public:
	virtual ~GameProgram() = 0;

private:
	virtual void update() = 0;
	virtual bool init(Engine* engine) = 0;

};

}
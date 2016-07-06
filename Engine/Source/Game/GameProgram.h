#pragma once

namespace xe {

class GameProgram {

	friend class Engine;

	public:
		virtual ~GameProgram() = 0;

		virtual void update() = 0;

	private:
		virtual bool init() = 0;
};

}
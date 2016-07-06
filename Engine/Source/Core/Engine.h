#pragma once

#include "Common/Type.h"

namespace xe {

class Window;
class GameProgram;
class Renderer;

class Engine {
	public:
		Engine();

		bool init();
		void start();

		void setGameProgram(GameProgram* gameProgram);
		void setGameProgram(Renderer* renderer);

	private:
		void run();
		void update();
		void render();
		void stop();
		void dispose();

		Window* m_window;

		// by setter
		GameProgram* m_gameProgram;
		Renderer* m_renderer;
};

}
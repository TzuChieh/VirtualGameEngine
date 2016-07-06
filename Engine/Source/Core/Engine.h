#pragma once

namespace xe {

class Window;

class Engine {
	public:
		Engine();

		bool init();
		void start();

	private:
		void run();
		void update();
		void render();
		void stop();
		void dispose();

		Window* m_window;
};

}
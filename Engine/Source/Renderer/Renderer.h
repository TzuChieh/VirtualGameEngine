#pragma once

namespace xe {

class Renderer {
	public:
		virtual void render() = 0;

	private:
		virtual bool init() = 0;
};

}
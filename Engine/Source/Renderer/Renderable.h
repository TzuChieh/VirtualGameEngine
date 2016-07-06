#pragma once

namespace xe {

class Renderable {
	public:
		virtual ~Renderable() = 0;

		virtual void render() const = 0;
};

}
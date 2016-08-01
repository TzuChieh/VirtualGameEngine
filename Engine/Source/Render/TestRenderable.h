#pragma once

#include "Renderable.h"

namespace xe {

class TestRenderable : public Renderable {
	public:
		virtual ~TestRenderable() override;

		virtual void render() const override;
};

}
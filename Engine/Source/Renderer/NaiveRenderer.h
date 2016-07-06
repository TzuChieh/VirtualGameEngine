#pragma once

#include "Renderer.h"

namespace xe {

class NaiveRenderer : public Renderer{
	public:
		virtual void render() override;

	private:
		virtual bool init() override;
};

}
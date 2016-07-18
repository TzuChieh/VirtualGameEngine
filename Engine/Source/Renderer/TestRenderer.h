#pragma once

#include "Renderer.h"

namespace xe
{

class TestRenderer : public Renderer
{
public:
	virtual ~TestRenderer() override;

	virtual void render() override;

private:
	virtual bool init() override;
	virtual void decompose() override;
};

}
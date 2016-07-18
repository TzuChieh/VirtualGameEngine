#pragma once

#include "Renderer.h"

namespace xe
{

class NaiveRenderer : public Renderer
{
public:
	virtual ~NaiveRenderer() override;

	virtual void render() override;

private:
	virtual bool init() override;
	virtual void decompose() override;
};

}
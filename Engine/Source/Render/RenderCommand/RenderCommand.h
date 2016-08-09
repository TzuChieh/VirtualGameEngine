#pragma once

namespace xe
{

class RenderCommand
{
public:
	virtual ~RenderCommand() = 0;

	virtual void execute() = 0;
};

}
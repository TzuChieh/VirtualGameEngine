#pragma once

#include "GpuCommand.h"

#include <queue>

namespace ve
{

class GpuCommandQueue final
{
public:

	void queue(const GpuCommand& command);

	bool isEmpty() const;

	GpuCommand& getFirst();
	void popFirst();

private:
	std::queue<GpuCommand> m_queue;
};

}
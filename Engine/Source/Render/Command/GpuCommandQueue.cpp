#include "GpuCommandQueue.h"

using namespace ve;

void GpuCommandQueue::queue(const GpuCommand& command)
{
	m_queue.push(command);
}

bool GpuCommandQueue::isEmpty() const
{
	return m_queue.empty();
}

GpuCommand& GpuCommandQueue::getFirst()
{
	return m_queue.front();
}

void GpuCommandQueue::popFirst()
{
	m_queue.pop();
}
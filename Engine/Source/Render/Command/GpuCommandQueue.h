#pragma once

#include <queue>
#include <functional>

namespace ve
{

class GpuCommandQueue final
{
public:
	
	void queue(const std::function<void()>& command);

	bool isEmpty() const;

	std::function<void()>& getFirst();
	void popFirst();

private:
	std::queue<std::function<void()>> m_queue;
};

}
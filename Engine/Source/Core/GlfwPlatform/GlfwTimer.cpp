#include "GlfwTimer.h"
#include "Core/glfw.h"

using namespace xe;

float64 GlfwTimer::getCurrentTimeS() const
{
	return static_cast<float64>(glfwGetTime());
}

float64 GlfwTimer::getCurrentTimeMs() const
{
	return static_cast<float64>(glfwGetTime() * 1000.0);
}
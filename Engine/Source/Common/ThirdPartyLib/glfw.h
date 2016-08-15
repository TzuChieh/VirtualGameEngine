#pragma once

// According to glfw's documentation, it's header must be included "after"
// external GL function loading library like glew, and this header would
// guarantee that.

#ifndef __glew_h__

	#include "glew.h"
	#include <GLFW/glfw3.h>

#else

	#include <GLFW/glfw3.h>

#endif
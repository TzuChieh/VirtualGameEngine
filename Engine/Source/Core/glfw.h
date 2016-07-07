#pragma once

// According to glfw's documentation, it's header must be included after
// external GL function loading library like glew, and this header would
// guarantee that.

#ifndef __glew_h__

	// If GLEW_STATIC is defined, the order of <GL/glew.h> and <GLFW/glfw3.h> doesn't matter;
	// otherwise <GL/glew.h> must include before <GLFW/glfw3.h>. Here we still include glew
	// before glfw just to be safe.

	#ifndef GLEW_STATIC
		#define GLEW_STATIC
	#endif

	#include <GL/glew.h>
	#include <GLFW/glfw3.h>

#else

	#include <GLFW/glfw3.h>

#endif
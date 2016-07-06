#pragma once

// here we assumed that we will use GLEW with GLFW only (this might change)

#ifndef GLEW_STATIC
	#define GLEW_STATIC
#endif

// If GLEW_STATIC is defined, the order of <GL/glew.h> and <GLFW/glfw3.h> doesn't matter;
// otherwise <GL/glew.h> must include before <GLFW/glfw3.h>.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
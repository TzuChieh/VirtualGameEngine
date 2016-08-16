// Do this before #include "stb_image.h" in *one* C or C++ file to create 
// the implementation.
#define STB_IMAGE_IMPLEMENTATION

// Define STBI_NO_FAILURE_STRINGS to avoid compiling these strings at all, 
// and STBI_FAILURE_USERMSG to get slightly more user-friendly ones.
#define STBI_FAILURE_USERMSG

#include <stb_image.h>
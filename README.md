## What is Virtual Game Engine?
Virtual Game Engine (VGE) is a game engine written in C++. The project is currently in development, and we are still learning new things at the mean time. We are fairly new to C++, but we work hard to make it easy to use, powerful and high-performance at the same time. It is very possible that we have done something in the wrong way, and you are welcome to tell us about it (contact information at the bottom)!

## How to Build
#### Preparation
* VGE utilizes the powerful C++11 and should be built in x64 mode (including all dependencies)
* VGE depends on the following libraries
 * GLFW   (https://github.com/glfw/glfw)
 * GLEW   (https://github.com/nigels-com/glew)
 * Assimp (http://www.assimp.org/index.html)
 * stb    (https://github.com/nothings/stb)
* For the dependencies, you can either
 * use our pre-compiled binaries (SORRY! WE ARE STILL WORKING ON THEM!)
 * grab the code from above repositories and compile them into binaries by yourself

#### Compile VGE
* folder "Engine" should be the root directory
* link the aforementioned libraries

 For people who use the pre-compiled binaries (SORRY! WE ARE STILL WORKING ON THEM!):
 * link "???"

 For people who want to compile the libraries by themselves
 * for GLFW, link glfw<*>.lib (it is okay to use the dll version if you want)
 * for GLEW, link glew<*>.lib (you MUST use the static version)
 * for Assimp, link assimp<*>.lib and zlib<*>.lib (it is okay to use the dll version if you want)

* Finally, set the following folders as additional include directories
 * "./Source"
 * the "include" directory of GLFW
 * the "include" directory of GLEW
 * the "include" directory of Assimp
 * the directory where "stb_image.h" sits
* compile!

## Developers
#### P.W. Huang
* (to be edited)

#### T.C. Chang
* Facebook Page: https://www.facebook.com/tokzin3d/
* YouTube Channel: https://www.youtube.com/channel/UCKdlogjqjuFsuv06wajp-2g
* E-mail: b01502051@ntu.edu.tw

If you have any questions or ideas about our project, feel free to send us an e-mail (=
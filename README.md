## What is Xeno Game Engine?
Xeno Game Engine (XGE) is a cross-platform game engine written in C++. The project is currently in development, and we are still learning new things at the mean time. We are fairly new to C++, but we work hard to make it easy to use, powerful and high-performance at the same time. It is very possible that we have done something in the wrong way, and you are welcome to tell us about it (contact information at the bottom)!

## How to Build
#### Preparation
* XGE uses C++11 and should be built in x64 mode (including all dependencies)
* XGE depends on the following libraries
 * GLFW (https://github.com/glfw/glfw)
 * GLEW (https://github.com/nigels-com/glew)
* For the dependencoes, you can either
 * use our pre-compiled binaries (Windows debug mode only, details in later section)
 * grab the code from above repositories and compile them into binaries by yourself

#### Compile XGE
* folder "Engine" should be the root directory
* Link Libraries

 For people who use the pre-compiled binaries (Windows debug mode only):
 * link "./Library/ThirdParty/glfw/lib/windows/glfw3d.lib"
 * link "./Library/ThirdParty/glew/lib/windows/glew32d.lib"

 For people who compile the libraries by theirselves
 * for GLFW, link glfw<*>.lib (it is okay to use dll version if you want)
 * for GLEW, link glew<*>.lib (you MUST use static library)

* finally, set the following folders as additional include directories
 * "./Source"
 * the "include" directory of GLFW
 * the "include" directory of GLEW
* compile!

## Developers
#### P.W. Huang
* (to be edited)

#### T.C. Chang
* Facebook Page: https://www.facebook.com/tokzin3d/
* YouTube Channel: https://www.youtube.com/channel/UCKdlogjqjuFsuv06wajp-2g
* E-mail: b01502051@ntu.edu.tw

If you have any questions or ideas about our project, feel free to send us an e-mail (=
## What is Xeno Game Engine?
Xeno Game Engine (XGE) is a cross-platform game engine written in C++. We are fairly new to C++, but we work hard to make it easy to use, powerful and high-performance at the same time. It is very possible that we have done something in the wrong way, and you are welcome to tell us about it (contact information at the bottom)!

## How to Build
#### Preparation
- XGE uses C++11 and should be built in x64 mode (including all dependencies)
- XGE depends on the following libraries
 - GLFW (https://github.com/glfw/glfw)
 - GLEW (https://github.com/nigels-com/glew)

Grab the code from above repositories and compile them into binaries.

#### Compile
- folder "Engine" should be the root directory
- place the libraries
 - for GLFW, put glfw3.lib into "./Library/ThirdParty/glfw/lib" (it is okay to use dll if you want)
 - for GLEW, put glew32s.lib into "./Library/ThirdParty/glfw/lib" (you MUST use static library)
- set the following folders as additional include directories
 - "./Source"
 - "./Library/ThirdParty/glfw/include"
 - "./Library/ThirdParty/glew/include"
- link the libraries and compile!

## Developers
#### T.C. Chang
- Facebook Page: https://www.facebook.com/tokzin3d/
- YouTube Channel: https://www.youtube.com/channel/UCKdlogjqjuFsuv06wajp-2g
- E-mail: b01502051@ntu.edu.tw

#### P.W. Huang
- (to be edited)

If you have any questions or ideas about our project, feel free to send us an e-mail (= <br />